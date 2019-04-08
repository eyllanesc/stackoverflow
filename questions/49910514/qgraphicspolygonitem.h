#ifndef QGRAPHICSPOLYGONITEM_H
#define QGRAPHICSPOLYGONITEM_H

#include <QGraphicsPolygonItem>

class QLabel;
class GraphicsProxyWidget;

class DiagramItem : public QGraphicsPolygonItem {
  QLabel *label;
  GraphicsProxyWidget *pMyProxy;

public:
  explicit DiagramItem(QGraphicsItem *parent = nullptr);
  void setText(const QString &text);
};

#endif // QGRAPHICSPOLYGONITEM_H
