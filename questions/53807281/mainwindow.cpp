#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      m_scene(new QGraphicsScene{this}) {
  ui->setupUi(this);
  ui->leftView->setScene(m_scene);
  ui->rightView->setScene(m_scene);
  m_scene->addPixmap(QPixmap(":/qt.png"));

  ui->rightView->setModifiers(Qt::AltModifier);
  ui->leftView->setModifiers(Qt::ControlModifier);
}

MainWindow::~MainWindow() { delete ui; }
