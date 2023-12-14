#include "updserver.h"

UpdServer::UpdServer(Settings *settings, QWidget *parent) : QWidget(parent)
{
    this->settings = settings;
    height = 0;

    setGeometry(100, 300, 250, 150);
    setWindowTitle("Alimetr Server");

    connectionLabel = new QLabel(kConnectionToClientText + kNo, this);
    heightLabel = new QLabel(kCurrentHeightText + "0" + kPromptText, this);

    heightSlider = new QSlider(Qt::Horizontal, this);
    heightSlider->setRange(kMinHeight, kMaxHeight);
    heightSlider->setValue(0);
    connect(heightSlider, SIGNAL(sliderMoved(int)), this,
    SLOT(SearchSliderMoved(int)));

    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addWidget(connectionLabel);
    vBoxLayout->addWidget(heightLabel);
    vBoxLayout->addWidget(heightSlider);


    udpSoket = new QUdpSocket(this);
    MessageToClient();

    signalTimer = new QTimer(this);
    connect(signalTimer, SIGNAL(timeout()), this, SLOT(MessageToClient()));
    signalTimer->start(1000 / kSignalFrequency);

    udpSoket = new QUdpSocket(this);
    udpSoket->bind(settings->GetPort()+1);
    connect(udpSoket, &QUdpSocket::readyRead, this, [this]() { GetData(); });
}

void UpdServer::UpdateUI()
{
    if(isConnect)
        connectionLabel->setText(kConnectionToClientText + kYes);
    else
        connectionLabel->setText(kConnectionToClientText + kNo);

    heightLabel->setText(kCurrentHeightText + QString::number(height) + kPromptText);
}

void UpdServer::GetData()
{
    QByteArray datagram;
    do {
        datagram.resize(udpSoket->pendingDatagramSize());
        udpSoket->readDatagram(datagram.data(), datagram.size());
    } while(udpSoket->hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_0);

    Message2 mes;
    in >> mes;

    if((qint16)mes.header != kMessage2Header)
        return;

    if(isConnect == false){
        isConnect = true;
        UpdateUI();
    }
}

void UpdServer::MessageToClient()
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    Message1 message(height);
    out << message;

    udpSoket->writeDatagram(byteArray, settings->GetAddress(), settings->GetPort());
}

void UpdServer::SearchSliderMoved(int value)
{
    if(height == value)
        return;

    height = value;
    UpdateUI();
}
