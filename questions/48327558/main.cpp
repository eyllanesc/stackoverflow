#include "twolistselection.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TwoListSelection w;
  QStringList input;
  for (int i = 0; i < 10; i++) {
    input << QString("item-%1").arg(i);
  }
  w.addAvailableItems(input);
  w.show();
  return a.exec();
}
