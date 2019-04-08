#ifndef FLOWER_H
#define FLOWER_H

#include <QObject>

class Flower : public QObject {
  Q_OBJECT
public:
  explicit Flower(QObject *parent = nullptr);
  Q_SLOT void onClicked();
};

#endif // FLOWER_H
