#ifndef RECT_H
#define RECT_H
#include <QPoint>

class Rect
{
public:
    Rect(QPoint A, QPoint B);

    QPoint A;
    QPoint B;

    QPoint getA();
    QPoint getB();
    void setA(int a1, int a2);
    void setB(int b1, int b2);
};

#endif // RECT_H
