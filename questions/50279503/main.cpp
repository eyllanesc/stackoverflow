#include "optionlist.h"
#include "scene.h"

#include <QApplication>
#include <QGraphicsView>
#include <QHBoxLayout>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget w;

  QHBoxLayout lay(&w);

  OptionList list;

  QGraphicsView view;
  view.setScene(new Scene);
  lay.addWidget(&list);
  lay.addWidget(&view);
  w.show();

  return a.exec();
}
