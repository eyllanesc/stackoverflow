#include "custompage.h"

#include <QMouseEvent>
#include <QPainter>

CustomPage::CustomPage(QWidget *parent) : QWizardPage(parent) {
  mRect = QRect(100, 100, 100, 100);
  mRadius = 10;
}

QRect CustomPage::rect() const { return mRect; }

void CustomPage::setRect(const QRect &rect) {
  if (mRect == rect)
    return;
  mRect = rect;
  update();
}

int CustomPage::radius() const { return mRadius; }

void CustomPage::setRadius(int radius) {
  if (mRadius == radius)
    return;
  mRadius = radius;
  update();
}

void CustomPage::setHideRect(bool value) {
  hideRect = value;
  update();
}

void CustomPage::paintEvent(QPaintEvent *event) {
  QWizardPage::paintEvent(event);

  if (!hideRect) {
    QPainter painter(this);
    painter.setPen(Qt::darkBlue);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(mRect);

    QList<QPoint> points;
    points << mRect.topLeft() << mRect.topRight() << mRect.bottomLeft()
           << mRect.bottomRight();

    painter.setBrush(QBrush(Qt::green));
    for (QPoint point : points) {
      painter.drawEllipse(point, mRadius, mRadius);
    }
  }
}

void CustomPage::mousePressEvent(QMouseEvent *event) {
  if (!hideRect) {
    QList<QPoint> points;
    points << mRect.topLeft() << mRect.topRight() << mRect.bottomLeft()
           << mRect.bottomRight();

    QPoint p = event->pos();

    for (int i = 0; i < points.length(); i++) {
      QPoint point = points.at(i);
      QPainterPath path;
      path.addEllipse(point, mRadius, mRadius);
      if (path.contains(p)) {
        mPosition = (Position)i;
        emit onClicked(mPosition);
        break;
      }
    }
  }
  QWizardPage::mousePressEvent(event);
}
