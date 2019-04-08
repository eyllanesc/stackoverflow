#include "graphicsscene.h"

#include <QDrag>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QMimeData>
#include <QWidget>

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  auto its = items(QRectF(event->scenePos() - QPointF(1, 1), QSize(3, 3)));
  auto val = std::find_if(its.constBegin(), its.constEnd(), [](auto const &it) {
    return it->type() > QGraphicsItem::UserType;
  });
  if (val == its.constEnd())
    return;
  if (event->button() == Qt::RightButton) {
    showContextMenu(event->scenePos());
  } else {
    createDrag(event->scenePos(), event->widget(), *val);
  }
}

void GraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
  QByteArray byteArray = event->mimeData()->data("Item");
  QGraphicsPixmapItem *item =
      *reinterpret_cast<QGraphicsPixmapItem **>(byteArray.data());
  QGraphicsItem *item_parent = itemAt(event->scenePos(), QTransform());
  item->setParentItem(item_parent);
}

QGraphicsPixmapItem *GraphicsScene::findPixmapItem(QGraphicsItem *item) {
  auto chs = item->childItems();
  auto val = std::find_if(chs.constBegin(), chs.constEnd(), [](auto const &it) {
    return static_cast<QGraphicsPixmapItem *>(it) != Q_NULLPTR;
  });
  return val == chs.constEnd() ? Q_NULLPTR
                               : static_cast<QGraphicsPixmapItem *>(*val);
}

void GraphicsScene::createDrag(const QPointF &pos, QWidget *widget,
                               QGraphicsItem *item) {
  QGraphicsPixmapItem *pix = findPixmapItem(item);
  if (pix == Q_NULLPTR)
    return;
  QByteArray byteArray(reinterpret_cast<char *>(&pix),
                       sizeof(QGraphicsPixmapItem *));
  QDrag *drag = new QDrag(widget);
  QMimeData *mimeData = new QMimeData;
  mimeData->setData("Item", byteArray);
  drag->setMimeData(mimeData);
  drag->setHotSpot(pos.toPoint() - pix->scenePos().toPoint());
  drag->setPixmap(pix->pixmap());
  drag->start();
}

void GraphicsScene::showContextMenu(const QPointF &pos) {
  QGraphicsItem *item = itemAt(pos, QTransform());
  menu = new QMenu("Menu");
  submenu = menu->addMenu(QIcon(":/img/pix.png"), "Pix");
  picture = submenu->addAction(QIcon(":/img/pix.png"), "Pix");
  connect(picture, &QAction::triggered, [item, this]() { addPixBlock(item); });
  menu->exec(QCursor::pos());
}

void GraphicsScene::addPixBlock(QGraphicsItem *item) {
  if (findPixmapItem(item))
    return;
  QPixmap pixmap(":/img/pix.png");
  pix = addPixmap(pixmap.scaled(70, 50));
  if (pix->parentItem() != item)
    pix->setParentItem(item);
}
