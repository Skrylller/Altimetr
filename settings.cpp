#include "settings.h"

Settings::Settings(QObject *parrent) : QObject(parrent)
{
    QSettings sett(kSettingsFile, QSettings::IniFormat);

    address = sett.value("ADDRESS", "127.0.0.1").toString();
    port = sett.value("PORT", 8002).toUInt();
}

QHostAddress Settings::GetAddress()
{
    qint32 addressInt;
    QStringList tempAddress = address.split(".");
    if(tempAddress.size() == 4){
        addressInt = tempAddress.at(3).toInt()
                | tempAddress.at(2).toInt() << 8
                | tempAddress.at(1).toInt() << 16
                | tempAddress.at(0).toInt() << 24;

        return QHostAddress(addressInt);
    }

    return QHostAddress();
}

qint16 Settings::GetPort()
{
    return port;
}
