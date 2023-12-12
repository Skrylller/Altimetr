#include "updclient.h"

UpdClient::UpdClient(QWidget *parent) : QWidget(parent)
{
    resize(250, 150);
    setWindowTitle("Alimetr Client");

    connectionLabel = new QLabel(kConnectionToServerText + kNo, this);
    heightLabel = new QLabel(kCurrentHeightText + "0", this);

    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addWidget(connectionLabel);
    vBoxLayout->addWidget(heightLabel);

    signalTimer = new QTimer(this);
    connect(signalTimer, SIGNAL(timeout()), this, SLOT(MessageToServer()));
    signalTimer->start(1000 / kSignalFrequency);

    udpSoket = new QUdpSocket(this);
    udpSoket->bind(8001);
    connect(udpSoket, &QUdpSocket::readyRead, this, [this]() { GetData(); });
}

void UpdClient::GetData()
{
    int str;
    QByteArray datagram;

    do {
        datagram.resize(udpSoket->pendingDatagramSize());
        udpSoket->readDatagram(datagram.data(), datagram.size());
    } while(udpSoket->hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_0);

    in >> str;
    heightLabel->setText(kCurrentHeightText + QString::number(str));
}

void UpdClient::MessageToServer()
{
}

