#include "popup.h"

#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

PopUp::PopUp(QWidget *parent) : QWidget(parent)
{
    auto flags = windowFlags();
    setWindowFlags(flags | Qt::WindowStaysOnTopHint| Qt::FramelessWindowHint | Qt::ToolTip);

    setAttribute(Qt::WA_TranslucentBackground);

    setLayout(new QVBoxLayout);
    label = new QLabel("Popup", this);
    layout()->addWidget(label);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    resize(QSize(200, 100));
}

void PopUp::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Prepare the popup dimensions
    QRect roundedRectDimensions;
    roundedRectDimensions.setX(rect().x() + 2);
    roundedRectDimensions.setY(rect().y() + 2);
    roundedRectDimensions.setWidth(rect().width() - 4);
    roundedRectDimensions.setHeight(rect().height() - 4);

    painter.setBrush(QBrush(Qt::lightGray));

    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidth(3);
    painter.setPen(pen);

    // Draw the popup body
    painter.drawRoundedRect(roundedRectDimensions, 15, 15);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));
}
