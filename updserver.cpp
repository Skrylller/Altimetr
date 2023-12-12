#include "updserver.h"

UpdServer::UpdServer(QWidget *parent) : QWidget(parent)
{
    resize(250, 150);
    setWindowTitle("Alimetr Server");

    connectionLabel = new QLabel(kConnectionToServerText + kNo, this);
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
}

void UpdServer::UpdateUI()
{
    heightLabel->setText(kCurrentHeightText + QString::number(height) + kPromptText);
}

void UpdServer::MessageToClient()
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << height;

    udpSoket->writeDatagram(byteArray, QHostAddress::LocalHost, 8001);
}

void UpdServer::SearchSliderMoved(int value)
{
    if(height == value)
        return;

    height = value;
    UpdateUI();
}
