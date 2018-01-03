#ifndef DRAW_ON_QIMAGE_H
#define DRAW_ON_QIMAGE_H

#include <QPainter>
#include <QQuickPaintedItem>

class DrawItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
public:
    DrawItem(QQuickItem *parent = Q_NULLPTR):QQuickPaintedItem(parent){
        setAntialiasing(true);
    }
    void paint(QPainter *painter){
        painter->setFont(mFont);
        painter->drawText(boundingRect(), "Hello");
    }
    QFont font() const{
        return mFont;
    }
    void setFont(const QFont &font){
        if(mFont == font)
            return;
        mFont = font;
        emit fontChanged();
        update();
    }

signals:
    void fontChanged();
private:
    QFont mFont;
};

#endif // DRAW_ON_QIMAGE_H
