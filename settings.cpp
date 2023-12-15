#include "settings.h"

Settings::Settings(QObject *parrent) : QObject(parrent)
{
    QSettings sett(kSettingsFile, QSettings::IniFormat);

    addressServer = sett.value("ADDRESS_SERVER", "127.0.0.1").toString();
    portServer = sett.value("PORT_SERVER", 8001).toUInt();
    addressClient = sett.value("ADDRESS_CLIENT", "127.0.0.1").toString();
    portClient = sett.value("PORT_CLIENT", 8002).toUInt();
}

QHostAddress Settings::GetAddressServer()
{
    return ConvertToHostAddress(&addressServer);
}

QHostAddress Settings::GetAddressClient()
{
    return ConvertToHostAddress(&addressClient);
}

qint16 Settings::getPortClient() const
{
    return portClient;
}

qint16 Settings::getPortServer() const
{
    return portServer;
}

QHostAddress Settings::ConvertToHostAddress(QString const *str)
{
    qint32 addressInt;
    QStringList tempAddress = str->split(".");
    if(tempAddress.size() == 4){
        addressInt = tempAddress.at(3).toInt()
                | tempAddress.at(2).toInt() << 8
                | tempAddress.at(1).toInt() << 16
                | tempAddress.at(0).toInt() << 24;

        return QHostAddress(addressInt);
    }

    return QHostAddress();
}
