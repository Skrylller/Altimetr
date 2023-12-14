#ifndef UPDCLIENT_H
#define UPDCLIENT_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <ConstValues.h>
#include <QTimer>
#include <QUdpSocket>
#include <QByteArray>
#include <QDataStream>
#include <heightindicatorwidget.h>
#include <MessageStructs.h>
#include <settings.h>

class UpdClient : public QWidget
{
    Q_OBJECT

public:
    UpdClient(Settings *settings, QWidget *parent = nullptr);

private:
    int const kSignalFrequency = 2;

    Settings *settings;

    QLabel *connectionLabel;
    QLabel *heightLabel;
    HeightIndicatorWidget *indicator;

    QUdpSocket* udpSoket;
    QTimer *sendMessageTimer = nullptr;
    QTimer *checkConnectionTimer = nullptr;

    int height;
    bool isConnect;
    time_t lastConnectionTime;

    void UpdateUI();

private slots:
    void MessageToServer();

    void GetData();

    void CheckConnection();

};
#endif // UPDCLIENT_H
