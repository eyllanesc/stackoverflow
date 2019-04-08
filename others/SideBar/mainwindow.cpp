#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  for (int i = 0; i < 6; ++i)
    ui->widget->addAction(QString("Action %1").arg(i),
                          QIcon(QString(":/icons/icon%1").arg(i)));
}

MainWindow::~MainWindow() { delete ui; }
