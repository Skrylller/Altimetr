#ifndef SETTINGS_H
#define SETTINGS_H


#include <QSettings>
#include <QVariant>
#include <QHostAddress>

class Settings : QObject
{
public:
    Settings(QObject *parrent = nullptr);

    QHostAddress GetAddress();

    qint16 GetPort();

private:
    QString const kSettingsFile = "settings.ini";

    QString address;
    qint16 port;
};

#endif // SETTINGS_H
