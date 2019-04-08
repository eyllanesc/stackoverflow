#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  w.setGeometry(100, 100, 900, 700);
  return a.exec();
}
