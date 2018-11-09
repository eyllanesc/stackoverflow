#ifndef GRAPHICSPROXYWIDGET_H
#define GRAPHICSPROXYWIDGET_H

#include <QGraphicsProxyWidget>

class GraphicsProxyWidget: public QGraphicsProxyWidget{
public:
    using QGraphicsProxyWidget::QGraphicsProxyWidget;
    QRectF boundingRect() const override;
};
#endif // GRAPHICSPROXYWIDGET_H
