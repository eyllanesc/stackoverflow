#include "my3dwindow.h"
#include <QDebug>
#include <QKeyEvent>

My3DWindow::My3DWindow(QScreen *screen) : Qt3DExtras::Qt3DWindow(screen) {}

My3DWindow::~My3DWindow() {}

void My3DWindow::keyPressEvent(QKeyEvent *ev) {
  switch (ev->key()) {
  case Qt::Key_W:
    qDebug() << "Key is pressed";
    break;
  default:
    break;
  }
}
