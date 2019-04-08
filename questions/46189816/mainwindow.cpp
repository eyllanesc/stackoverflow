#include "mainwindow.h"
#include "htmldelegate.h"
#include "ui_mainwindow.h"

#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->listWidget->setItemDelegate(new HtmlDelegate);
}

MainWindow::~MainWindow() { delete ui; }
