#ifndef UPDSERVER_H
#define UPDSERVER_H

#include <QLabel>
#include <QBoxLayout>
#include <QSlider>
#include <QByteArray>
#include <QDataStream>
#include <MessageStructs.h>
#include <updwidget.h>

class UpdServer: public UpdWidget
{
    Q_OBJECT

public:
    UpdServer(Settings *settings, QWidget *parent = nullptr);

private:
    int const kSignalFrequency = 25;

    QVBoxLayout *vBoxLayout;
    QLabel *connectionLabel;
    QLabel *heightLabel;
    QSlider *heightSlider;

    int height;

    void UpdateUI() override;

private slots:
    void Message() override;

    void GetData() override;

    void SearchSliderMoved(int value);
};
#endif // UPDSERVER_H
