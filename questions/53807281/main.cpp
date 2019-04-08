#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.resize(2 * 640, 2 * 480);
  w.show();

  return a.exec();
}
