#include "graphicsproxywidget.h"
#include "qgraphicspolygonitem.h"

#include <QApplication>
#include <QGraphicsView>
#include <QTimer>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QGraphicsView w;
  QGraphicsScene *scene = new QGraphicsScene;
  w.setScene(scene);
  auto it = new DiagramItem;
  QPolygonF myPolygon({QPointF(-120, -80), QPointF(-70, 80), QPointF(120, 80),
                       QPointF(70, -80), QPointF(-120, -80)});
  it->setPolygon(myPolygon);
  scene->addItem(it);

  QTimer::singleShot(1000, [it]() { it->setText("some text"); });
  w.show();
  return a.exec();
}
