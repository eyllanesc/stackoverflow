#include "stopmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  StopMainWindow w;
  w.show();

  return a.exec();
}
