#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCamera>
#include <QCameraInfo>
#include <QVBoxLayout>
#include <QVideoWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_viewfinder = new QVideoWidget;
  QVBoxLayout *lay = new QVBoxLayout(ui->centralWidget);
  lay->addWidget(m_viewfinder);
  m_camera = new QCamera(QCameraInfo::defaultCamera());
  m_camera->setViewfinder(m_viewfinder);

  m_camera->start();
}

MainWindow::~MainWindow() {
  m_camera->stop();
  delete m_viewfinder;
  delete m_camera;
  delete ui;
}
