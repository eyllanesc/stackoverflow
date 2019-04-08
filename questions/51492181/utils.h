#ifndef UTILS_H
#define UTILS_H

#include <QDataStream>
#include <QFont>
#include <QGraphicsLineItem>
#include <QPen>

QDataStream &operator<<(QDataStream &out, QGraphicsItem *item) {
  out << item->pos() << item->scale() << item->rotation() << item->transform()
      << item->transformOriginPoint() << item->flags() << item->isEnabled()
      << item->isSelected() << item->zValue();
  return out;
}
QDataStream &operator>>(QDataStream &in, QGraphicsItem *&item) {
  QPointF pos;
  qreal scale;
  qreal rotation;
  QTransform transform;
  QPointF transformOriginPoint;
  QGraphicsItem::GraphicsItemFlags flags;
  bool isEnabled;
  bool isSelected;
  qreal zValue;
  in >> pos >> scale >> rotation >> transform >> transformOriginPoint >>
      flags >> isEnabled >> isSelected >> zValue;
  item->setPos(pos);
  item->setScale(scale);
  item->setRotation(rotation);
  item->setTransform(transform);
  item->setTransformOriginPoint(transformOriginPoint);
  item->setFlags(flags);
  item->setEnabled(isEnabled);
  item->setSelected(isSelected);
  item->setZValue(zValue);
  return in;
}

QDataStream &operator<<(QDataStream &out, QAbstractGraphicsShapeItem *item) {
  out << dynamic_cast<QGraphicsItem *>(item);
  out << item->pen() << item->brush();
  return out;
}
QDataStream &operator>>(QDataStream &in, QAbstractGraphicsShapeItem *&item) {
  QGraphicsItem *tmp = dynamic_cast<QGraphicsItem *>(item);
  in >> tmp;
  QPen pen;
  QBrush brush;
  in >> pen >> brush;
  item->setBrush(brush);
  item->setPen(pen);
  return in;
}

QDataStream &operator<<(QDataStream &out, QGraphicsEllipseItem *item) {
  out << dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  out << item->rect() << item->startAngle() << item->spanAngle();
  return out;
}

QDataStream &operator>>(QDataStream &in, QGraphicsEllipseItem *&item) {
  QAbstractGraphicsShapeItem *tmp =
      dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  in >> tmp;
  QRectF rect;
  int startAngle;
  int spanAngle;
  in >> rect >> startAngle >> spanAngle;
  item->setRect(rect);
  item->setStartAngle(startAngle);
  item->setSpanAngle(spanAngle);
  return in;
}

QDataStream &operator<<(QDataStream &out, QGraphicsPathItem *item) {
  out << dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  out << item->path();
  return out;
}

QDataStream &operator>>(QDataStream &in, QGraphicsPathItem *&item) {
  QAbstractGraphicsShapeItem *tmp =
      dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  in >> tmp;
  QPainterPath path;
  in >> path;
  item->setPath(path);
  return in;
}

QDataStream &operator<<(QDataStream &out, QGraphicsPolygonItem *item) {
  out << dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  out << item->polygon() << item->fillRule();
  return out;
}

QDataStream &operator>>(QDataStream &in, QGraphicsPolygonItem *&item) {
  QAbstractGraphicsShapeItem *tmp =
      dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  in >> tmp;
  QPolygonF polygon;
  int rule;
  in >> polygon >> rule;
  item->setPolygon(polygon);
  item->setFillRule(Qt::FillRule(rule));
  return in;
}

QDataStream &operator<<(QDataStream &out, QGraphicsRectItem *item) {
  out << dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  out << item->rect();
  return out;
}

QDataStream &operator>>(QDataStream &in, QGraphicsRectItem *&item) {
  QAbstractGraphicsShapeItem *tmp =
      dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  in >> tmp;
  QRectF rect;
  in >> rect;
  item->setRect(rect);
  return in;
}

QDataStream &operator<<(QDataStream &out, QGraphicsSimpleTextItem *item) {
  out << dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  out << item->text() << item->font();
  return out;
}

QDataStream &operator>>(QDataStream &in, QGraphicsSimpleTextItem *&item) {
  QAbstractGraphicsShapeItem *tmp =
      dynamic_cast<QAbstractGraphicsShapeItem *>(item);
  in >> tmp;
  QString text;
  QFont font;
  in >> text >> font;
  item->setText(text);
  item->setFont(font);
  return in;
}

QDataStream &operator<<(QDataStream &out, QGraphicsLineItem *item) {
  out << dynamic_cast<QGraphicsItem *>(item);
  out << item->pen() << item->line();
  return out;
}

QDataStream &operator>>(QDataStream &in, QGraphicsLineItem *&item) {
  QGraphicsItem *tmp = dynamic_cast<QGraphicsItem *>(item);
  in >> tmp;
  QPen pen;
  QLineF line;
  in >> pen >> line;
  item->setPen(pen);
  item->setLine(line);
  return in;
}

QDataStream &operator<<(QDataStream &out, QGraphicsPixmapItem *item) {
  out << dynamic_cast<QGraphicsItem *>(item);
  out << item->pixmap() << item->offset() << item->transformationMode()
      << item->shapeMode();
  return out;
}

QDataStream &operator>>(QDataStream &in, QGraphicsPixmapItem *&item) {
  QGraphicsItem *tmp = dynamic_cast<QGraphicsItem *>(item);
  in >> tmp;
  QPixmap pixmap;
  QPointF offset;
  int transformationMode;
  int shapeMode;
  in >> pixmap >> offset >> shapeMode >> transformationMode;
  item->setPixmap(pixmap);
  item->setOffset(offset);
  item->setTransformationMode(Qt::TransformationMode(transformationMode));
  item->setShapeMode(QGraphicsPixmapItem::ShapeMode(shapeMode));
  return in;
}

static void saveItems(QList<QGraphicsItem *> items, QDataStream &out) {
  for (QGraphicsItem *item : items) {
    out << item->type();
    switch (item->type()) {
    case QGraphicsLineItem::Type:
      out << dynamic_cast<QGraphicsLineItem *>(item);
      break;
    case QGraphicsSimpleTextItem::Type:
      out << dynamic_cast<QGraphicsSimpleTextItem *>(item);
      break;
    case QGraphicsRectItem::Type:
      out << dynamic_cast<QGraphicsRectItem *>(item);
      break;
    case QGraphicsPolygonItem::Type:
      out << dynamic_cast<QGraphicsPolygonItem *>(item);
      break;
    case QGraphicsPathItem::Type:
      out << dynamic_cast<QGraphicsPathItem *>(item);
      break;
    case QGraphicsPixmapItem::Type:
      out << dynamic_cast<QGraphicsPixmapItem *>(item);
      break;
    }
  }
}

static QList<QGraphicsItem *> readItems(QDataStream &in) {
  QList<QGraphicsItem *> items;
  int type;
  while (!in.atEnd()) {
    in >> type;
    switch (type) {
    case QGraphicsLineItem::Type: {
      QGraphicsLineItem *item = new QGraphicsLineItem;
      in >> item;
      items << item;
      break;
    }
    case QGraphicsSimpleTextItem::Type: {
      QGraphicsSimpleTextItem *item = new QGraphicsSimpleTextItem;
      in >> item;
      items << item;
      break;
    }
    case QGraphicsRectItem::Type: {
      QGraphicsRectItem *item = new QGraphicsRectItem;
      in >> item;
      items << item;
      break;
    }
    case QGraphicsPolygonItem::Type: {
      QGraphicsPolygonItem *item = new QGraphicsPolygonItem;
      in >> item;
      items << item;
      break;
    }
    case QGraphicsPathItem::Type: {
      QGraphicsPathItem *item = new QGraphicsPathItem;
      in >> item;
      items << item;
      break;
    }
    case QGraphicsPixmapItem::Type: {
      QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
      in >> item;
      items << item;
      break;
    }
    }
  }
  return items;
}

#endif // UTILS_H
