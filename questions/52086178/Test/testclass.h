#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QWidget>

class TestClass : public QWidget {
  Q_OBJECT
  Q_PROPERTY(QColor color MEMBER m_color NOTIFY colorChanged)
public:
  TestClass(QWidget *parent = nullptr);
signals:
  void colorChanged();

private:
  QColor m_color;
};

#endif
