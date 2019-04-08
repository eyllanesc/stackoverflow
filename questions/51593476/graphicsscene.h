#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene {
  Q_OBJECT
public:
  GraphicsScene(QObject *parent = nullptr);
  void moveSelecteds(Qt::Alignment aligment);
private slots:
  void onSelectionChanged();

private:
  void move(QGraphicsItem *ref, QList<QGraphicsItem *> others,
            Qt::Alignment aligment);
  QGraphicsItem *mRef;
};
#endif // GRAPHICSSCENE_H
