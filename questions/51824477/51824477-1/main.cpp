#include "mainwindow.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  double counter = 0;
  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&w, &counter]() {
    w.dataGaugeChanged(counter);
    counter++;
    if (counter > 100)
      counter = 0;
  });

  timer.start(100);

  return a.exec();
}
