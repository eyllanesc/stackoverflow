#include "mainwindow.h"
#include "custombutton.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  CustomButton *custom = new CustomButton(this);
  custom->resize(200, custom->height());
}

MainWindow::~MainWindow() { delete ui; }
