#include <QApplication>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

class AnimatedGraphicsLineItem : public QObject, public QGraphicsLineItem {
  Q_OBJECT
  Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
  using QGraphicsLineItem::QGraphicsLineItem;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QGraphicsView w;
  QGraphicsScene scene;
  w.setScene(&scene);
  w.resize(640, 480);
  w.show();

  auto group = new QParallelAnimationGroup;

  const std::vector<std::pair<QPointF, QPointF>> points{
      {QPointF(0, 0), QPointF(100, 0)},
      {QPointF(100, 0), QPointF(100, 100)},
      {QPointF(-100, -100), QPointF(0, 100)}};
  for (auto &p : points) {
    auto line = new AnimatedGraphicsLineItem(QLineF(p.first, p.second));
    line->setOpacity(0);
    auto fadeAnimation = new QPropertyAnimation(line, "opacity");
    scene.addItem(line);
    fadeAnimation->setDuration(1000);
    fadeAnimation->setStartValue(0);
    fadeAnimation->setEndValue(1);
    fadeAnimation->setEasingCurve(QEasingCurve::InBack);
    group->addAnimation(fadeAnimation);
  }

  if (group->animationCount() > 0)
    group->start(QAbstractAnimation::DeleteWhenStopped);

  return a.exec();
}

#include "main.moc"
