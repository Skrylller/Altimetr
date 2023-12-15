#include "updclient.h"

UpdClient::UpdClient(Settings *settings, QWidget *parent) : UpdWidget(settings, parent)
{
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

    //подключаем updSoket к порту
    udpSoket->bind(settings->getPortClient());

    //запускаем таймер отправки сообщения
    messageTimer->start(1000 / kSignalFrequency);
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

void UpdClient::Message()
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    Message2 message;
    out << message;

    udpSoket->writeDatagram(byteArray, settings->GetAddressServer(), settings->getPortServer());
}


