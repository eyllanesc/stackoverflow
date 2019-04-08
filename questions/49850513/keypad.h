#ifndef KEYPAD_H
#define KEYPAD_H

#include <QWidget>

class Keypad : public QWidget {
public:
  explicit Keypad(QWidget *parent = nullptr);

private:
  struct Keys {
    QString name;
    int key;
  };
  Q_SLOT void on_clicked();
};

#endif // KEYPAD_H
