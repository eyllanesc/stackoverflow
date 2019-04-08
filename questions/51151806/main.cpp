#include <QApplication>

#include "displayimage.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  DisplayImage w;
  w.displayImg(QImage(":/test.jpeg"));
  w.show();

  return a.exec();
}
