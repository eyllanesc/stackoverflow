#include "graphicsproxywidget.h"
#include <QWidget>

QRectF GraphicsProxyWidget::boundingRect() const{
    if(widget())
        return QRectF(widget()->rect());
    return QGraphicsProxyWidget::boundingRect();
}
