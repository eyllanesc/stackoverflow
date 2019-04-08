#include <QCoreApplication>

#include "httpcontroller.h"

#include <QDebug>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  HttpController controller;

  qDebug() << controller.Get("http://doc.qt.io/qt-4.8/qtnetwork-module.html");

  return a.exec();
}
