#ifndef SPLASHITEM_H
#define SPLASHITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPropertyAnimation>

class SplashItem : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
  explicit SplashItem(QObject *parent = nullptr);
  void setStartValue(const QPointF &p);
  void setEndValue(const QPointF &p);

private:
  Q_SLOT void onFinished();
  Q_SLOT void verifyCollide();
  QPropertyAnimation *m_animation;
};

#endif // SPLASHITEM_H
