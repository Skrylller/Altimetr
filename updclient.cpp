#include "updclient.h"

UpdClient::UpdClient(Settings *settings, QWidget *parent) : QWidget(parent)
{
    this->settings = settings;

    setGeometry(100, 100, 600, 650);
    setWindowTitle("Alimetr Client");

    connectionLabel = new QLabel(kConnectionToServerText + kNo, this);
    heightLabel = new QLabel(kCurrentHeightText + "0", this);
    indicator = new  HeightIndicatorWidget(this);

    QWidget *topWidget = new QWidget(this);
    QVBoxLayout *vTopBoxLayout = new QVBoxLayout(topWidget);
    vTopBoxLayout->addWidget(connectionLabel);
    vTopBoxLayout->addWidget(heightLabel);
    topWidget->setFixedHeight(50);

    QVBoxLayout *vAdditionalBoxLayout = new QVBoxLayout(this);
    vAdditionalBoxLayout->addWidget(topWidget);
    vAdditionalBoxLayout->addWidget(indicator);

    sendMessageTimer = new QTimer(this);
    connect(sendMessageTimer, SIGNAL(timeout()), this, SLOT(MessageToServer()));
    sendMessageTimer->start(1000 / kSignalFrequency);

    checkConnectionTimer = new QTimer(this);
    connect(checkConnectionTimer, SIGNAL(timeout()), this, SLOT(CheckConnection()));
    checkConnectionTimer->start(1000);

    udpSoket = new QUdpSocket(this);
    udpSoket->bind(settings->GetPort());
    connect(udpSoket, &QUdpSocket::readyRead, this, [this]() { GetData(); });
}

void UpdClient::UpdateUI()
{
    if(isConnect)
        connectionLabel->setText(kConnectionToServerText + kYes);
    else
        connectionLabel->setText(kConnectionToServerText + kNo);
}

void UpdClient::GetData()
{
    QByteArray datagram;

    do {
        datagram.resize(udpSoket->pendingDatagramSize());
        udpSoket->readDatagram(datagram.data(), datagram.size());
    } while(udpSoket->hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_0);

    Message1 mes;
    in >> mes;

    if((qint16)mes.header != kMessage1Header)
        return;

    heightLabel->setText(kCurrentHeightText + QString::number(mes.height));
    indicator->setHeight(mes.height);

    if(isConnect == false){
        isConnect = true;
        UpdateUI();
    }

    lastConnectionTime = time(NULL);
}

void UpdClient::MessageToServer()
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    Message2 message;
    out << message;

    udpSoket->writeDatagram(byteArray, settings->GetAddress(), settings->GetPort()+1);
}

void UpdClient::CheckConnection()
{
    if(time(NULL) - lastConnectionTime >= kConnectDelay && isConnect == true){
        isConnect = false;
        UpdateUI();
    }
}


