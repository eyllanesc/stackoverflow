#include <QApplication>
#include <QMainWindow>
#include <QTime>

#include "win.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  Win *widget = new Win;

  widget->show();
  return app.exec();
}
