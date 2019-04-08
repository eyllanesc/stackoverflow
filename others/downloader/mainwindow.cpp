#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->progressBar->setValue(0);
  dl = new QtDownload(this);

  ui->pushButton->setEnabled(false);

  connect(dl, SIGNAL(progress(qint64, qint64)), this,
          SLOT(myslot(qint64, qint64)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::myslot(qint64 recieved, qint64 total) {
  ui->progressBar->setMaximum(total);
  ui->progressBar->setValue(recieved);
}

void MainWindow::on_pushButton_clicked() {
  dl->setTarget(ui->lineEdit->text());

  dl->download();
}

void MainWindow::on_pushButton_2_clicked() {
  QString filters("Document files (*.pdf);");
  QString filename = QFileDialog::getSaveFileName(0, "Save file",
                                                  QDir::currentPath(), filters);
  if (!filename.isEmpty()) {
    ui->lineEdit_2->setText(filename);
    dl->setFilename(filename);
    if (!ui->lineEdit_2->text().isEmpty()) {
      ui->pushButton->setEnabled(true);
    }
  }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1) {
  if (!ui->lineEdit_2->text().isEmpty()) {
    ui->pushButton->setEnabled(!arg1.isEmpty());
  } else {
    ui->pushButton->setEnabled(false);
  }
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1) {
  if (!ui->lineEdit->text().isEmpty()) {
    ui->pushButton->setEnabled(!arg1.isEmpty());
  } else {
    ui->pushButton->setEnabled(false);
  }
}
