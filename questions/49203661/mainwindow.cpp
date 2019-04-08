#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  for (int i = 0; i < 10; i++) {
    QComboBox *combo = new QComboBox;
    for (int j = 0; j < 10; j++) {
      combo->addItem(QString("%1-%2").arg(i).arg(j));
    }
    ui->verticalLayout->addWidget(combo);
  }

  connect(ui->pushButton, &QPushButton::clicked, [this]() {
    QLayoutItem *child;
    if ((child = ui->verticalLayout->takeAt(0)) != 0) {
      ui->verticalLayout->addItem(child);
    }
  });
}

MainWindow::~MainWindow() { delete ui; }
