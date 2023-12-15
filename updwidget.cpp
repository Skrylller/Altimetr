#include "updwidget.h"

UpdWidget::UpdWidget(Settings *settings, QWidget *parent) : QWidget(parent)
{
    this->settings = settings;
    isConnect = false;

    //создание сокета
    udpSoket = new QUdpSocket(this);
    connect(udpSoket, &QUdpSocket::readyRead, this, [this]() { GetData(); });

    //создание таймера отправки сообщения
    messageTimer = new QTimer(this);
    connect(messageTimer, SIGNAL(timeout()), this, SLOT(Message()));

    //создание таймера проверки подключения
    checkConnectionTimer = new QTimer(this);
    connect(checkConnectionTimer, SIGNAL(timeout()), this, SLOT(CheckConnection()));
    checkConnectionTimer->start(100);
}

void UpdWidget::CheckConnection()
{
    if(time(NULL) - lastConnectionTime >= kConnectDelay && isConnect == true){
        isConnect = false;
        UpdateUI();
    }
}
