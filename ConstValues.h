#ifndef CONSTTEXT_H
#define CONSTTEXT_H

#include <qstring.h>

static int const kMinHeight = 0;
static int const kMaxHeight = 9999;

static QString const kConnectionToServerText = "Связь с сервером: ";
static QString const kCurrentHeightText = "Текущая высота: ";
static QString const kPromptText = " (Может изменяться от " + QString::number(kMinHeight) + " до " + QString::number(kMaxHeight) + " м)";
static QString const kNo = "Нет";
static QString const kYes = " Да";

#endif // CONSTTEXT_H
