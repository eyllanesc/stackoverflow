#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQmlEngine>

#include <QDebug>
#include <QQuickItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnUpdatePos_clicked() {
  QQuickItem *item = ui->quickWidget->rootObject();
  QObject *object = item->findChild<QObject *>("mapItem");
  QVariant posx = QVariant(-12.0464);
  QVariant posy = QVariant(-77.0428);

  if (object != NULL) {
    QMetaObject::invokeMethod(object, "recenter", Q_ARG(QVariant, posx),
                              Q_ARG(QVariant, posy));
  }
}
