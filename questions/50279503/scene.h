#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
class QGraphicsSceneDragDropEvent;

class Scene : public QGraphicsScene {
public:
  Scene(QObject *parent = nullptr);

protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
  void dropEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // SCENE_H
