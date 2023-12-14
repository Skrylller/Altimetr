#include "heightindicatorwidget.h"

HeightIndicatorWidget::HeightIndicatorWidget(QWidget* parent) : QWidget(parent)
{
    setGeometry(100, 100, 600, 600);
    setHeight(0);
}

void HeightIndicatorWidget::setHeight(int height)
{
    m_height = height;
    update();
}

void HeightIndicatorWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QPen apen = QPen();

    int w = width();
    int h =  height();

    painter.fillRect(0, 0, w, h, Qt::black);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate((float)w / 2, (float)h / 2);

    int side = qMin(w, h);
    painter.scale(side / 200.0, side / 200.0);

    //рисуем текст подсказку
    apen.setWidth(kWideLineWidth);
    apen.setColor(Qt::gray);
    painter.setPen(apen);

    int fontHeight = 12;
    painter.setFont(QFont("Arial", fontHeight));
    int sideTextBox = 100;
    QRect metersPromptRect(-(float)sideTextBox / 2, -(float)kThousandArrowRadius / 2 - (float)sideTextBox / 2, sideTextBox, sideTextBox);
    painter.drawText(metersPromptRect, Qt::AlignCenter, "H");
    metersPromptRect = QRect(-(float)sideTextBox / 2, (float)kThousandArrowRadius / 2 - (float)sideTextBox / 2, sideTextBox, sideTextBox);
    painter.drawText(metersPromptRect, Qt::AlignCenter, "Метры");

    //рисуем метки на высотометре
    apen.setWidth(kWideLineWidth);
    apen.setColor(Qt::white);
    painter.setPen(apen);

    int NumThousandPoint = kMaxHeight % 1000 != 0 ? kMaxHeight / 1000 + 1 : kMaxHeight / 1000;
    int NumHundredPoint = 10;
    int NumTwentyPoint = NumHundredPoint * 5;

    for (int i = 0; i < NumHundredPoint; ++i) {
        painter.drawLine(0, kHundredArrowRadius - 1, 0, kHundredArrowRadius - kHundredLineLength);
        painter.rotate(360 / (float)NumHundredPoint);
    }

    for (int i = 0; i < NumThousandPoint; ++i) {
        painter.drawLine(0, kThousandArrowRadius + (float)kTwentyLineLength / 2, 0, kThousandArrowRadius - (float)kTwentyLineLength / 2);
        painter.rotate(360 / (float)NumThousandPoint);
    }

    apen.setWidth(kNarrowLineWidth);
    painter.setPen(apen);

    for (int i = 0; i < NumTwentyPoint; ++i) {
        if(i % 5 != 0)
            painter.drawLine(0, kHundredArrowRadius, 0, kHundredArrowRadius - kTwentyLineLength);
        painter.rotate(360 / (float)NumTwentyPoint);
    }

    //рисуем текст циферблата
    QPoint point(0, -(kHundredArrowRadius - (float)(kHundredArrowRadius - kThousandArrowRadius) / 2));

    painter.save();
    for(int i = 0; i < NumHundredPoint; ++i){
        painter.rotate(360 / (float)NumHundredPoint * i);
        painter.translate(point);
        painter.rotate(-360 / (float)NumHundredPoint * i);
        QRectF textRect(-(float)fontHeight / 2, -(float)fontHeight / 2, fontHeight, fontHeight);
        painter.drawText(textRect, Qt::AlignCenter, QString::number(i));
        painter.restore();
        painter.save();
    }

    //рисуем круги на высотометре
    QRectF rectangleHundred(-kHundredArrowRadius, -kHundredArrowRadius, kHundredArrowRadius * 2, kHundredArrowRadius * 2);
    painter.drawArc(rectangleHundred, 0, 360 * 16);

    QRectF rectangleThousand(-kThousandArrowRadius, -kThousandArrowRadius, kThousandArrowRadius * 2, kThousandArrowRadius * 2);
    painter.drawArc(rectangleThousand, 0, 360 * 16);

    //рисуем стрелки высотометра
    apen.setColor(Qt::gray);
    apen.setWidth(1);
    painter.setPen(apen);

    painter.setBrush(QColor(255,255,255));

    static const QPoint thousandHand[5] = {
        QPoint(4, 5),
        QPoint(-4, 5),
        QPoint(-8, -(float)kThousandArrowRadius * 0.60),
        QPoint(0, -(float)kThousandArrowRadius * 0.95),
        QPoint(8, -(float)kThousandArrowRadius * 0.60),
    };

    static const QPoint hundredHand[5] = {
        QPoint(5, 5),
        QPoint(-5, 5),
        QPoint(-5, -(float)kHundredArrowRadius * 0.80),
        QPoint(0, -(float)kHundredArrowRadius * 0.95),
        QPoint(5, -(float)kHundredArrowRadius * 0.80),
    };

    int numValues = (kMaxHeight - kMinHeight + 1);
    if(numValues != 0){
        painter.save();
        painter.rotate(360 / (float)numValues * m_height);
        painter.drawConvexPolygon(thousandHand, 5);
        painter.restore();

        painter.rotate(360 / (float)1000 * (m_height % 1000));
        painter.drawConvexPolygon(hundredHand, 5);
        painter.restore();
    }

    //рисуем панель с текстом в центре
    int rectWidth = (float)fontHeight * 0.8 * std::to_string(kMaxHeight).length() + 4;
    int rectHeight = fontHeight + 4;
    QRect heightTextRect(-(float)rectWidth / 2, -(float)rectHeight / 2, rectWidth, rectHeight);
    painter.fillRect(heightTextRect, Qt::black);
    painter.drawRect(heightTextRect);
    painter.drawText(heightTextRect, Qt::AlignCenter, QString::number(m_height));
}
