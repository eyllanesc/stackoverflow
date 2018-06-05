#ifndef CUSTOMRECT_H
#define CUSTOMRECT_H

#include <QGraphicsPixmapItem>

class MyArrow;

class CustomRect : public QGraphicsRectItem
{
public:
    CustomRect (const QRectF& rect);
    void addLine(MyArrow *line);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void moveLineToCenter(QPointF newPos);

private:
    QList<MyArrow *> arrows;
};
#endif // CUSTOMRECT_H
