#include "camerafeed.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CameraFeed w;
  w.show();

  return a.exec();
}
