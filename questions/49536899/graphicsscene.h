#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>

class QMenu;
class QAction;

class GraphicsScene : public QGraphicsScene {
public:
  using QGraphicsScene::QGraphicsScene;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
  QGraphicsPixmapItem *findPixmapItem(QGraphicsItem *item);
  void createDrag(const QPointF &pos, QWidget *widget, QGraphicsItem *item);
  void showContextMenu(const QPointF &pos);
  void addPixBlock(QGraphicsItem *item);

  QMenu *menu;
  QMenu *submenu;
  QAction *picture;
  QGraphicsPixmapItem *pix;
};

#endif // GRAPHICSSCENE_H
