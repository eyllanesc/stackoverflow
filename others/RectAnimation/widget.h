#ifndef WIDGET_H
#define WIDGET_H

#include <QPaintEvent>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(QRect nrect READ nRect WRITE setNRect)

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

  QRect nRect() const;
  void setNRect(const QRect &rect);

protected:
  void paintEvent(QPaintEvent *event);

private:
  QRect mRect;
};

#endif // WIDGET_H
