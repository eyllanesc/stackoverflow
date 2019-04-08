#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QParallelAnimationGroup>

class GraphicsView : public QGraphicsView {
  Q_OBJECT
public:
  GraphicsView(QWidget *parent = Q_NULLPTR);

  void closeEvent(QCloseEvent *event);

private:
  QParallelAnimationGroup *group;
};

#endif // GRAPHICSVIEW_H
