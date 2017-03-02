#include "glwidget.h"
#include <QTimer>

GLWidget::GLWidget(QWidget *parent):QOpenGLWidget(parent)
{
    sprite = new CSprite2D(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLWidget::animate);
    timer->start(50);
}

void GLWidget::animate()
{
    QPoint nextPos = sprite->getPos() + direction * QPoint(10, 10);
    if(!rect().contains(nextPos)){
        direction *= -1;
    }
    sprite->setPos(sprite->getPos() + direction * QPoint(10, 10));
    update();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    sprite->paint(&painter, event);
}
