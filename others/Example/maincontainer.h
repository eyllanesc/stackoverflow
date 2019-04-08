#ifndef MAINCONTAINER_H
#define MAINCONTAINER_H

#include "logicclass.h"
#include <QWidget>

namespace Ui {
class MainContainer;
}

class MainContainer : public QWidget {
  Q_OBJECT

public:
  explicit MainContainer(QWidget *parent = 0);
  ~MainContainer();

private:
  Ui::MainContainer *ui;
  LogicClass *logic;
};

#endif // MAINCONTAINER_H
