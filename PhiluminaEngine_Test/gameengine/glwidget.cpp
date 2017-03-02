#include "glwidget.h"
#include <QTimer>

GLWidget::GLWidget(QWidget *parent):QOpenGLWidget(parent)
{
    sprite = new CSprite2D(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLWidget::animate);
    connect(sprite, &CSprite2D::onChanged, [this]{update();});
    timer->start(50);
}

void GLWidget::animate()
{
    QPoint deltaPos =  QPoint(qrand() % 20 , qrand() % 20);
    if(!rect().contains(sprite->getPos() + direction * deltaPos)){
        direction *= -1;
    }
    sprite->setPos(sprite->getPos() + direction * deltaPos) ;
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    sprite->paint(&painter, event);
}
