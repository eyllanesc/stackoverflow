#include "customslider.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CustomSlider w;
  w.show();

  return a.exec();
}
