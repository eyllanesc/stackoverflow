#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

class TestWidget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(EnumTest test READ test WRITE setTest)
public:
  TestWidget(QWidget *parent = 0);

  enum EnumTest { ENUM0, ENUM1, ENUM2, ENUM3 };
  Q_ENUM(EnumTest)

  EnumTest test() const;
  void setTest(const EnumTest &test);

private:
  EnumTest mTest;
};

#endif
