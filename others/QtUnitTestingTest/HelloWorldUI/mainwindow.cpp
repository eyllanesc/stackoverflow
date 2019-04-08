#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  hw = new HelloWorldLib();
  connect(ui->pushButton, SIGNAL(clicked()), hw, SLOT(someSlot()));
}

MainWindow::~MainWindow() { delete ui; }
