#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QGraphicsView>

class DisplayImage : public QGraphicsView {
  Q_OBJECT
public:
  DisplayImage(QWidget *parent = 0);
  void displayImg(const QImage &image);

  bool eventFilter(QObject *watched, QEvent *event);

private:
  QGraphicsScene *scene;
  QPixmap pixmap;
  QGraphicsPixmapItem *pixmapItem;
};
#endif // DISPLAYIMAGE_H
