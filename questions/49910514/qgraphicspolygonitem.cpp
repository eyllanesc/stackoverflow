#include "qgraphicspolygonitem.h"
#include "graphicsproxywidget.h"

#include <QLabel>

DiagramItem::DiagramItem(QGraphicsItem *parent) : QGraphicsPolygonItem(parent) {
  label = new QLabel;
  pMyProxy = new GraphicsProxyWidget(this);
  pMyProxy->setWidget(label);
  label->setTextInteractionFlags(Qt::TextEditorInteraction);
  label->setStyleSheet("QLabel { background-color : red; color : blue; }");
  setText(QString("I AM A SQARE DADADA"));
  setBrush(Qt::green);
}

void DiagramItem::setText(const QString &text) {
  label->setText(text);
  label->adjustSize();
  pMyProxy->setPos(boundingRect().center() - label->rect().center());
}
