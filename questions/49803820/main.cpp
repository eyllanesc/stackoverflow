#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QGraphicsView w;
  QGraphicsScene *scene = new QGraphicsScene;
  w.setScene(scene);

  QList<QGraphicsPixmapItem *> items;

  for (const QString &filename : {":/character.png", ":/owl.png"}) {
    QGraphicsPixmapItem *item = scene->addPixmap(QPixmap(filename));
    item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    item->setFlag(QGraphicsItem::ItemIsMovable, true);
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    items << item;
  }

  items[1]->setPos(50, 22);
  if (items[0]->collidingItems().isEmpty())
    qDebug() << "there is no intersection";
  w.show();
  return a.exec();
}
