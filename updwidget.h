#ifndef UPDWIDGET_H
#define UPDWIDGET_H

#include <QWidget>
#include <settings.h>
#include <QUdpSocket>
#include <QTimer>
#include <ConstValues.h>

class UpdWidget: public QWidget
{
    Q_OBJECT

public:
    UpdWidget(Settings *settings, QWidget *parent = nullptr);

protected:
    Settings *settings;

    QUdpSocket* udpSoket;
    QTimer *messageTimer = nullptr;

    bool isConnect;
    time_t lastConnectionTime;

    virtual void UpdateUI() = 0;

private:
    QTimer *checkConnectionTimer = nullptr;

private slots:
    virtual void Message() = 0;

    virtual void GetData() = 0;

    void CheckConnection();
};

#endif // UPDWIDGET_H
