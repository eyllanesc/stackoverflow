#ifndef HELLOWORLDLIB_H
#define HELLOWORLDLIB_H

#include <QDebug>

class HelloWorldLib : public QObject {
  Q_OBJECT

public:
  HelloWorldLib() {}
  static bool returnTrue() { return true; }

public slots:
  void someSlot() { qDebug() << "test"; }
};

#endif // HELLOWORLDLIB_H
