#ifndef TEST_H
#define TEST_H

#include <QObject>

class test : public QObject {
  Q_OBJECT
public:
  explicit test(QObject *parent = nullptr);
  Q_INVOKABLE void testFunc();
};

#endif // TEST_H
