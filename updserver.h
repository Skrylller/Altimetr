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

class UpdServer: public QWidget
{
    Q_OBJECT

public:
    UpdServer(QWidget *parent = nullptr);

private:
    int const kSignalFrequency = 25;

    QVBoxLayout *vBoxLayout;
    QLabel *connectionLabel;
    QLabel *heightLabel;
    QSlider *heightSlider;

    QUdpSocket* udpSoket;
    QTimer *signalTimer = nullptr;

    int height;
    bool isConnect;

    void UpdateUI();

private slots:
    void MessageToClient();
    void SearchSliderMoved(int value);
};
#endif // UPDSERVER_H
