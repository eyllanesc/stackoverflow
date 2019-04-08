#include "demopromotedwidget.h"
#include "ui_demopromotedwidget.h"

DemoPromotedWidget::DemoPromotedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::DemoPromotedWidget) {
  ui->setupUi(this);
}

DemoPromotedWidget::~DemoPromotedWidget() { delete ui; }
