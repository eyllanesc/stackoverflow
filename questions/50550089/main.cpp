#include <QApplication>
#include <QFrame>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QFrame frame;
  frame.resize(320, 240);
  QSequentialAnimationGroup group;
  group.setLoopCount(-1);
  int minSize = 5;
  int maxSize = 30;
  int labelSize = 50;
  ;
  for (const QPoint &pos : {QPoint(0, 0), QPoint(0, 40), QPoint(0, 80)}) {
    QRect startVal = QRect(
        pos + (QPoint(labelSize, labelSize) + QPoint(-minSize, -minSize)) / 2,
        QSize(minSize, minSize));
    QRect endVal = QRect(
        pos + (QPoint(labelSize, labelSize) + QPoint(-maxSize, -maxSize)) / 2,
        QSize(maxSize, maxSize));
    QLabel *label = new QLabel(&frame);
    label->setGeometry(startVal);
    label->setPixmap(QPixmap(":/circle.png"));
    label->setScaledContents(true);
    label->setAlignment(Qt::AlignCenter);
    QPropertyAnimation *animation = new QPropertyAnimation(label, "geometry");
    animation->setStartValue(startVal);
    animation->setKeyValueAt(.5, endVal);
    animation->setEndValue(startVal);
    animation->setDuration(1000);
    group.addAnimation(animation);
  }
  group.start();
  frame.show();
  return a.exec();
}
