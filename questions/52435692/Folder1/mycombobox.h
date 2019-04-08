#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H
#include <QComboBox>

class MyComboBox : public QComboBox {
  Q_OBJECT
public:
  MyComboBox(QWidget *parent = nullptr) : QComboBox(parent) {
    addItem("My ComboBox");
  }

  virtual ~MyComboBox() {}
};
#endif // MYCOMBOBOX_H
