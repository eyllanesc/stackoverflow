
#include "rect.h"

Rect::Rect(QPoint A, QPoint B)
{
    A.setX(this->A.x());
    A.setY(this->A.y());
    B.setX(this->B.x());
    B.setY(this->B.y());
}

