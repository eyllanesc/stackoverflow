#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QModelIndex>
#include <QTime>
#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->treeWidget, &QTreeWidget::clicked, this, &QMainWindow::close);

  qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));

  for (int i = 0; i < 10; i++) {
    CSprite2D *sprite = new CSprite2D(this);
    sprite->setName(QString::number(i));
    sprite->setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
    ui->openGLWidget->addSprite(sprite);
  }
}

MainWindow::~MainWindow() { delete ui; }
