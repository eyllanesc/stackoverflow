#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "form.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  centralWidget()->setLayout(new QHBoxLayout);

  centralWidget()->layout()->addWidget(new Form);
}

MainWindow::~MainWindow() { delete ui; }
