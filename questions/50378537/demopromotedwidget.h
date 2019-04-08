#ifndef DEMOPROMOTEDWIDGET_H
#define DEMOPROMOTEDWIDGET_H

#include <QWidget>

namespace Ui {
class DemoPromotedWidget;
}

class : public QWidget {
  Q_OBJECT

public:
  explicit DemoPromotedWidget(QWidget *parent = 0);
  ~DemoPromotedWidget();

private:
  Ui::DemoPromotedWidget *ui;
};

#endif // DEMOPROMOTEDWIDGET_H
