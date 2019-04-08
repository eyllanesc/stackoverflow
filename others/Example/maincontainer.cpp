#include "maincontainer.h"
#include "ui_maincontainer.h"

#include <QPushButton>

MainContainer::MainContainer(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainContainer) {
  ui->setupUi(this);
  logic = new LogicClass(this);
  connect(ui->pushButton, &QPushButton::clicked, logic,
          &LogicClass::on_click_slot);
}

MainContainer::~MainContainer() { delete ui; }
