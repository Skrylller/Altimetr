#ifndef HEIGHTINDICATORWIDGET_H
#define HEIGHTINDICATORWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QBackingStore>
#include <QTime>
#include <ConstValues.h>
#include <QDebug>

class HeightIndicatorWidget : public QWidget
{
    Q_OBJECT

public:
    HeightIndicatorWidget(QWidget* parent = nullptr);

    void setHeight(int height);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int const kHundredArrowRadius = 90;
    int const kThousandArrowRadius = 50;

    int const kHundredLineLength = 10;
    int const kTwentyLineLength = 6;
    int const kThousandLineLength = 7;

    int const kWideLineWidth = 2;
    int const kNarrowLineWidth = 1;

    int m_height = 0;
};

#endif // HEIGHTINDICATORWIDGET_H
