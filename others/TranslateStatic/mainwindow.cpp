#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QTranslator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->comboBox->addItem("ITEM 1");
  ui->comboBox->addItem("ITEM 2");

  retranslate();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {

  QMessageBox::critical(
      this, QApplication::translate("MainWindow", "Titles", Q_NULLPTR),
      QApplication::translate("MainWindow", "Failed", Q_NULLPTR),
      QMessageBox::Ok);
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  QTranslator lang_translator;
  qApp->removeTranslator(&lang_translator);
  switch (index) {
  case 1:
    lang_translator.load(":/lang/es.qm");
    QCoreApplication::instance()->installTranslator(&lang_translator);
    ui->retranslateUi(this);
    retranslate();
    break;
  }
}

void MainWindow::retranslate() { ; }
