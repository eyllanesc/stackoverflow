#ifndef LINEITEM_H
#define LINEITEM_H

#include <QQuickPaintedItem>

class LineItem : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(
      QPoint startPos READ startPos WRITE setStartPos NOTIFY startPosChanged)
  Q_PROPERTY(QPoint endPos READ endPos WRITE setEndPos NOTIFY endPosChanged)
  Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY
                 lineColorChanged)
public:
  using QQuickPaintedItem::QQuickPaintedItem;
  void paint(QPainter *painter);

  QPoint startPos() const;
  void setStartPos(const QPoint &startPos);
  QPoint endPos() const;
  void setEndPos(const QPoint &endPos);
  QColor lineColor() const;
  void setLineColor(const QColor &lineColor);

signals:
  void startPosChanged();
  void endPosChanged();
  void lineColorChanged();

private:
  QPoint m_startPos;
  QPoint m_endPos;
  QColor m_lineColor;
};

#endif // LINEITEM_H
