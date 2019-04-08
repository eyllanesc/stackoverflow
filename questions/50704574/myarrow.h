#ifndef MYARROW_H
#define MYARROW_H

class CustomRect;

#include <QGraphicsPathItem>

class MyArrow : public QGraphicsPathItem {
public:
  MyArrow(CustomRect *rect);
  void updatePosition(QPointF p1, QPointF p2);

private:
  CustomRect *myrect;
};

#endif // MYARROW_H
