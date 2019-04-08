#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QSequentialAnimationGroup>
#include <QVariantAnimation>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QGraphicsView w;

  QGraphicsScene scene(0, 0, 640, 480);
  w.setScene(&scene);
  w.show();

  QGraphicsPixmapItem *logo = new QGraphicsPixmapItem(QPixmap(":/image.jpg"));
  scene.addItem(logo);

  QSequentialAnimationGroup group;

  QVariantAnimation animation_scale;
  animation_scale.setDuration(1000);
  animation_scale.setStartValue(2.0);
  animation_scale.setEndValue(0.5);

  QObject::connect(
      &animation_scale, &QVariantAnimation::valueChanged,
      [logo](const QVariant &value) { logo->setScale(value.toReal()); });

  animation_scale.start();

  QVariantAnimation animation_pos;
  animation_pos.setDuration(1000);
  animation_pos.setStartValue(QPointF(0, 0));
  animation_pos.setEndValue(QPointF(100, 100));

  QObject::connect(
      &animation_pos, &QVariantAnimation::valueChanged,
      [logo](const QVariant &value) { logo->setPos(value.toPointF()); });

  /**
   * it must indicate the center of rotation,
   * in this case it will be the center of the item
   */

  logo->setTransformOriginPoint(logo->boundingRect().center());
  QVariantAnimation animation_rotate;
  animation_rotate.setDuration(1000);
  animation_rotate.setStartValue(0);
  animation_rotate.setEndValue(360);

  QObject::connect(
      &animation_rotate, &QVariantAnimation::valueChanged,
      [logo](const QVariant &value) { logo->setRotation(value.toReal()); });

  group.addAnimation(&animation_scale);
  group.addAnimation(&animation_pos);
  group.addAnimation(&animation_rotate);

  group.start();

  return a.exec();
}
