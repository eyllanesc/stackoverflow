#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QLabel>
#include <QPushButton>

class CustomButton : public QPushButton {
  Q_OBJECT
public:
  explicit CustomButton(QWidget *parent = nullptr);

protected:
  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);

private:
  QLabel left;
  QLabel right;
  const QString leftqss = "QLabel { "
                          "background-color:blue;"
                          "}";
  const QString rightqss = "QLabel { "
                           "background-color:red;"
                           "}";
};

#endif // CUSTOMBUTTON_H
