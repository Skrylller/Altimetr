#ifndef CONSTTEXT_H
#define CONSTTEXT_H

#include <qstring.h>
#include <QDataStream>
int const kConnectDelay = 2;

int const kMinHeight = 0;
int const kMaxHeight = 9999;

QString const kConnectionToServerText = "Связь с сервером: ";
QString const kConnectionToClientText = "Связь с клиентом: ";
QString const kCurrentHeightText = "Текущая высота: ";
QString const kPromptText = " (Может изменяться от " + QString::number(kMinHeight) + " до " + QString::number(kMaxHeight) + " м)";
QString const kNo = "Нет";
QString const kYes = " Да";

#endif // CONSTTEXT_H

