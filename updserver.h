#ifndef UPDSERVER_H
#define UPDSERVER_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <ConstValues.h>
#include <QSlider>
#include <QTimer>
#include <QUdpSocket>
#include <QByteArray>
#include <QDataStream>
#include <MessageStructs.h>
#include <settings.h>

class UpdServer: public QWidget
{
    Q_OBJECT

public:
    UpdServer(Settings *settings, QWidget *parent = nullptr);

private:
    int const kSignalFrequency = 25;

    Settings *settings;

    QVBoxLayout *vBoxLayout;
    QLabel *connectionLabel;
    QLabel *heightLabel;
    QSlider *heightSlider;

    QUdpSocket* udpSoket;
    QTimer *signalTimer = nullptr;
    QTimer *checkConnectionTimer = nullptr;

    int height;
    bool isConnect;
    time_t lastConnectionTime;

    void UpdateUI();

private slots:
    void MessageToClient();

    void GetData();

    void SearchSliderMoved(int value);

    void CheckConnection();
};
#endif // UPDSERVER_H
