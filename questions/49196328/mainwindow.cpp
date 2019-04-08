#include "mainwindow.h"
#include "glwidget.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  glW = new GLWidget(0, 0);
  QGridLayout *layout1 = new QGridLayout();
  QWidget *centralWidget1 = new QWidget(this);
  centralWidget1->setLayout(layout1);

  layout1->addWidget(glW);
  setCentralWidget(centralWidget1);
}

MainWindow::~MainWindow() { delete ui; }
