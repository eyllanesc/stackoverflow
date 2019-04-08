#include "customrubberband.h"

#include <QPainter>

CustomRubberBand::CustomRubberBand(Shape s, QWidget *p) : QRubberBand(s, p) {
  setAttribute(Qt::WA_TranslucentBackground, true);
}

void CustomRubberBand::paintEvent(QPaintEvent *) {

  if (isVisible()) {
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setBrush(QBrush(QColor(85, 142, 253, 100)));
    painter.drawRect(rect());
  }
}
