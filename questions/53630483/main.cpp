#include "wizard.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Wizard w;
  w.show();
  return a.exec();
}
