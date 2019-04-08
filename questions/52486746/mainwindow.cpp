#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->quickWidget->rootContext()->setContextProperty("mainwindow", this);
  setTitle("Oslo");
  setCenter(QPointF(59.93, 10.76));
  ui->quickWidget->setSource(QUrl("qrc:/main.qml"));
}

MainWindow::~MainWindow() { delete ui; }

QString MainWindow::title() const { return m_title; }

void MainWindow::setTitle(const QString &title) {
  if (m_title == title)
    return;
  m_title = title;
  emit titleChanged();
}

QPointF MainWindow::center() const { return m_center; }

void MainWindow::setCenter(const QPointF &center) {
  if (m_center == center)
    return;
  m_center = center;
  emit centerChanged();
}
