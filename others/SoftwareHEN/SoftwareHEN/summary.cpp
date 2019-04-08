#include "summary.h"
#include "ui_summary.h"

Summary::Summary(QWidget *parent) : QWidget(parent), ui(new Ui::Summary) {
  ui->setupUi(this);
}

Summary::~Summary() { delete ui; }
