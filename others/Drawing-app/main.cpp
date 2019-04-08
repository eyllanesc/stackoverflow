#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  DrawApp::MainWindow window;
  window.show();

  return app.exec();
}
