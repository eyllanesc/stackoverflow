#include "graphicsscene.h"

#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QShortcut>
#include <random>

static void create_items(QGraphicsScene &scene) {

  std::default_random_engine generator;
  std::uniform_int_distribution<int> dist_size(30, 40);
  std::uniform_int_distribution<int> dist_pos(-50, 50);

  for (const QString &colorname : {"red", "green", "blue", "gray", "orange"}) {
    QRectF r(QPointF(dist_pos(generator), dist_pos(generator)),
             QSizeF(dist_size(generator), dist_size(generator)));
    auto item = new QGraphicsRectItem(r);
    item->setPos(QPointF(dist_pos(generator), dist_pos(generator)));
    item->setBrush(QColor(colorname));
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    scene.addItem(item);
  }
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  GraphicsScene scene;
  create_items(scene);
  QGraphicsView view(&scene);

  const QList<QPair<Qt::Key, Qt::Alignment>> k_a{
      {Qt::Key_Up, Qt::AlignTop},
      {Qt::Key_Down, Qt::AlignBottom},
      {Qt::Key_Left, Qt::AlignLeft},
      {Qt::Key_Right, Qt::AlignRight}};

  for (const QPair<Qt::Key, Qt::Alignment> &p : k_a) {
    QShortcut *shorcut = new QShortcut(p.first, &view);
    QObject::connect(
        shorcut, &QShortcut::activated,
        std::bind(&GraphicsScene::moveSelecteds, &scene, p.second));
  }

  view.resize(640, 480);
  view.show();

  return a.exec();
}
