#ifndef SETTINGS_H
#define SETTINGS_H


#include <QSettings>
#include <QVariant>
#include <QHostAddress>

class Settings : QObject
{
public:
    Settings(QObject *parrent = nullptr);

    QHostAddress GetAddressServer();

    QHostAddress GetAddressClient();

    qint16 getPortClient() const;

    qint16 getPortServer() const;

private:
    QString const kSettingsFile = "settings.ini";

    QString addressServer;
    qint16 portServer;
    QString addressClient;
    qint16 portClient;

    QHostAddress ConvertToHostAddress(QString const *str);
};

#endif // SETTINGS_H
