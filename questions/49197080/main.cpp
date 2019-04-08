#include "testsize.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  testsize w;
  w.show();

  return a.exec();
}
