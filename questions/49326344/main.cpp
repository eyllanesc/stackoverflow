#include "mainwindow.h"
#include "myserver.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow *w = MainWindow::instance();
  MyServer server;
  server.startServer();
  w->show();
  return a.exec();
}
