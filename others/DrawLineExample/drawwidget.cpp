#include "drawwidget.h"

#include <QPainter>
DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
}

void DrawWidget::addWidgets(const QWidget * from, const QWidget * to)
{
    list.append(WidgetsConnected{from , to});
    update();
}

void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for(const WidgetsConnected el: list){
        const QWidget* from = el.from;
        const QWidget* to = el.to;

        QPoint start =  from->mapToGlobal(from->rect().topRight() +  QPoint(0, from->height()/2));
        QPoint end = to->mapToGlobal(to->rect().topLeft() +  QPoint(0, to->height()/2));

        painter.drawLine(mapFromGlobal(start), mapFromGlobal(end));
    }
}
