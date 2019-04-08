#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton, &QPushButton::clicked, [=]() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open XML File 1"), "", tr("XML Files (*.txt)"));
    ui->lineEdit->setText(fileName);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::critical(this, "error", file.errorString());
      return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
      texts.append(in.readLine());
    }
    timer->start(1000);
    file.close();
  });

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, [=]() {
    if (!texts.isEmpty()) {
      ui->textEdit->append(texts.first());
      texts.pop_front();
    } else {
      timer->stop();
      qDebug() << "finish";
    }
  });
}

MainWindow::~MainWindow() { delete ui; }
