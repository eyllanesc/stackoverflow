#include <QApplication>
#include <QFrame>
#include <QLabel>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFrame frame;
    frame.resize(320, 240);
    QSequentialAnimationGroup group;
    int minSize = 5;
    int maxSize = 30;
    int labelSize = 50;;
    for(const QPoint & pos: {QPoint(0, 0), QPoint(0, 40), QPoint(0, 80)}){
        QLabel *label = new QLabel(&frame);
        label->resize(labelSize, labelSize);
        label->move(pos);
        label->setPixmap(QPixmap(":/circle.png"));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
        QPropertyAnimation *animation = new QPropertyAnimation(label, "geometry");
        QRect startVal = QRect(pos + (QPoint(labelSize, labelSize) + QPoint(-minSize, -minSize))/2 , QSize(minSize, minSize));
        QRect endVal = QRect(pos + (QPoint(labelSize, labelSize) + QPoint(-maxSize, -maxSize))/2 , QSize(maxSize, maxSize));
        animation->setStartValue(startVal);
        animation->setEndValue(endVal);
        group.addAnimation(animation);
    }
    QObject::connect(&group, &QAbstractAnimation::finished, [&group](){
        QAbstractAnimation::Direction direction = group.direction() == QAbstractAnimation::Forward ?
                    QAbstractAnimation::Backward : QAbstractAnimation::Forward;
        group.setDirection(direction);
        group.start();
    });
    group.start();
    frame.show();
    return a.exec();
}
