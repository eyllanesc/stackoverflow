#include "rectobject.h"

RectObject::RectObject(QObject *parent) : QObject(parent)
{    
}

QRect RectObject::rect() const
{
    return mRect;
}

void RectObject::setRect(const QRect &value)
{
    mRect = value;
}
