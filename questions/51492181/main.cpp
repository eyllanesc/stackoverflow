#include "utils.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QGraphicsView view(new QGraphicsScene);

  QGraphicsEllipseItem *eitem = view.scene()->addEllipse(
      QRect(10, 10, 80, 50), QPen(Qt::green), QBrush(Qt::black));
  eitem->setPos(100, 10);
  eitem->setRotation(60);

  QGraphicsLineItem *litem =
      view.scene()->addLine(QLineF(0, 0, 100, 100), QPen(Qt::red));
  litem->setPos(10, 10);
  litem->setRotation(100);

  QGraphicsRectItem *ritem = view.scene()->addRect(
      QRect(10, 0, 100, 100), QPen(Qt::blue), QBrush(Qt::red));
  ritem->setPos(10, 100);
  ritem->setRotation(10);

  QPainterPath path;
  path.moveTo(100, 100);
  path.lineTo(10, 0);
  path.addRect(QRect(0, 0, 100, 22));
  QGraphicsPathItem *pitem =
      view.scene()->addPath(path, QPen(Qt::green), QBrush(Qt::black));
  pitem->setPos(100, 22);
  pitem->setRotation(120);

  QGraphicsPixmapItem *pixmapitem = new QGraphicsPixmapItem;
  pixmapitem->setPixmap(QPixmap(":/image.png"));
  view.scene()->addItem(pixmapitem);

  QGraphicsItem::GraphicsItemFlags flags =
      QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
      QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemClipsToShape |
      QGraphicsItem::ItemClipsChildrenToShape;

  for (QGraphicsItem *it : view.scene()->items()) {
    it->setFlags(flags);
  }

  QTimer::singleShot(4000, [&view]() {
    qDebug() << "writing ...";
    QFile fileOut("file.txt");
    if (fileOut.open(QIODevice::WriteOnly)) {
      QDataStream out(&fileOut);
      saveItems(view.scene()->items(), out);
      fileOut.close();
      qDebug() << "clear items";
      view.scene()->clear();
    }
  });

  QTimer::singleShot(5000, [&view]() {
    qDebug() << "reading ...";
    QFile fileIn("file.txt");
    if (fileIn.open(QIODevice::ReadOnly)) {
      QDataStream in(&fileIn);
      QList<QGraphicsItem *> items = readItems(in);
      for (QGraphicsItem *item : items) {
        view.scene()->addItem(item);
      }
    }
  });

  view.show();
  return a.exec();
}
