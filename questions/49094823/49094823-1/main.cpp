#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class Pixmap : public QObject, public QGraphicsPixmapItem {

  Q_OBJECT
  Q_PROPERTY(qreal scale READ scale WRITE setScale)
  Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
  using QGraphicsPixmapItem::QGraphicsPixmapItem;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QGraphicsView w;

  QGraphicsScene scene(0, 0, 640, 480);
  w.setScene(&scene);
  w.show();

  Pixmap *logo = new Pixmap(QPixmap(":/image.jpg"));
  scene.addItem(logo);

  QSequentialAnimationGroup group;

  QPropertyAnimation animation_scale(logo, "scale");
  animation_scale.setDuration(1000);
  animation_scale.setStartValue(2.0);
  animation_scale.setEndValue(0.1);

  QPropertyAnimation animation_pos(logo, "pos");
  animation_pos.setDuration(1000);
  animation_pos.setStartValue(QPointF(0, 0));
  animation_pos.setEndValue(QPointF(100, 100));

  /**
   * it must indicate the center of rotation,
   * in this case it will be the center of the item
   */
  logo->setTransformOriginPoint(logo->boundingRect().center());
  QPropertyAnimation animation_rotate(logo, "rotation");
  animation_rotate.setDuration(1000);
  animation_rotate.setStartValue(0);
  animation_rotate.setEndValue(360);

  group.addAnimation(&animation_scale);
  group.addAnimation(&animation_pos);
  group.addAnimation(&animation_rotate);

  group.start();

  return a.exec();
}

#include "main.moc"
