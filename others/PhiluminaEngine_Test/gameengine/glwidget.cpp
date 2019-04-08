#include "glwidget.h"
#include <QDebug>
#include <QTimer>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &GLWidget::animate);
  timer->start(50);
}

void GLWidget::addSprite(CSprite2D *sprite) {
  sprites.append(sprite);
  // connect(sprite, &CSprite2D::onChanged, [this]{update();});
}

void GLWidget::animate() {
  foreach (CSprite2D *sprite, sprites) {
    QPoint deltaPos = QPoint(qrand() % 20, qrand() % 20);
    if (!rect().contains(sprite->pos() + direction * deltaPos)) {
      direction *= -1;
    }
    sprite->setPos(sprite->pos() + direction * deltaPos);
  }
  update();
}

void GLWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  const QRect &rect = event->rect();
  // painter->eraseRect(rect);
  painter.fillRect(rect, QBrush(QColor(0, 0, 0)));
  foreach (CSprite2D *sprite, sprites) { sprite->paint(&painter, event); }
}
