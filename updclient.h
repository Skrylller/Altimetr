#ifndef UPDCLIENT_H
#define UPDCLIENT_H

#include <QLabel>
#include <QBoxLayout>
#include <QByteArray>
#include <QDataStream>
#include <heightindicatorwidget.h>
#include <MessageStructs.h>
#include <updwidget.h>

class UpdClient : public UpdWidget
{
    Q_OBJECT

public:
    UpdClient(Settings *settings, QWidget *parent = nullptr);

private:
    int const kSignalFrequency = 2;

    QLabel *connectionLabel;
    QLabel *heightLabel;
    HeightIndicatorWidget *indicator;

    int height;

    void UpdateUI() override;

private slots:
    void Message() override;

    void GetData() override;

};
#endif // UPDCLIENT_H
