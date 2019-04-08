#include "cascadecolorhighlightwidgetitem.h"

#include <QApplication>
#include <QLabel>
#include <QTextDocument>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CascadeColorHighlightWidgetItem widget(1, QColor("red"));

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout,
                   [&widget]() { widget.getColorText(); });
  timer.start(100);
  widget.show();
  return a.exec();
}
