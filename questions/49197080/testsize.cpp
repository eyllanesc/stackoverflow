#include "testsize.h"

#include <QLabel>
#include <QResizeEvent>
#include <QVBoxLayout>

testsize::testsize(QWidget *parent) : QWidget(parent) {
  image = new QLabel(this);
  original_px = QPixmap(":/wallpaper.jpg");
  image->setPixmap(original_px);
  resize(640, 480);
}

testsize::~testsize() {}

void testsize::resizeEvent(QResizeEvent *event) {
  QPixmap px = original_px.scaled(event->size());
  image->setPixmap(px);
  image->resize(event->size());
  QWidget::resizeEvent(event);
}
