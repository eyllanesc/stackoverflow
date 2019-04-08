#include "speedometer.h"

#include <QApplication>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QListWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget w;
  QHBoxLayout *layout = new QHBoxLayout(&w);
  QListWidget listWidget;
  listWidget.setDragDropMode(QAbstractItemView::DragOnly);
  listWidget.addItems({"km/h", "ft/s", "m/s", "miles/h"});

  QGraphicsView view;
  QGraphicsScene scene;
  view.setScene(&scene);

  SpeedoMeter speed;
  scene.addWidget(&speed);
  layout->addWidget(&listWidget);
  layout->addWidget(&view);
  w.show();

  return a.exec();
}
