#include "csprite2d.h"

CSprite2D::CSprite2D(QObject *parent):QObject(parent)
{
    mPos = QPoint(10, 10);
}

CSprite2D::~CSprite2D()
{

}

QString CSprite2D::getName() const
{
    return mName;
}

void CSprite2D::setName(const QString &name)
{
    mName = name;
}

QPoint CSprite2D::getPos() const
{
    return mPos;
}

void CSprite2D::setPos(const QPoint &pos)
{
    mPos = pos;
}

void CSprite2D::paint(QPainter *painter, QPaintEvent *event)
{
    const QRect & rect = event->rect();
    //painter->eraseRect(rect);
    painter->fillRect(rect, QBrush(QColor(0, 0, 0)));
    QPen pen(Qt::white);
    painter->setPen(pen);
    QBrush brush(QColor(20, 80, 100));
    painter->setBrush(brush);
    painter->drawEllipse(mPos, 30, 30);
}
