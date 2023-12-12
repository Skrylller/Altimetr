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

class UpdClient : public QWidget
{
    Q_OBJECT

public:
    UpdClient(QWidget *parent = nullptr);

private:
    int const kSignalFrequency = 2;

    QVBoxLayout *vBoxLayout;
    QLabel *connectionLabel;
    QLabel *heightLabel;

    QUdpSocket* udpSoket;
    QTimer *signalTimer = nullptr;

    int height;
    bool isConnect;

private slots:
    void MessageToServer();

    void GetData();

};
#endif // UPDCLIENT_H
