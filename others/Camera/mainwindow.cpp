#include "mainwindow.h"

#include <QCameraInfo>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

  QWidget *centralWidget = new QWidget(this);
  this->setCentralWidget(centralWidget);
  layout = new QHBoxLayout(centralWidget);

  m_QPushButton_calibration = new QPushButton("Calibrate", this);
  connect(m_QPushButton_calibration, SIGNAL(released()), this,
          SLOT(handleButton()));

  QList<QCameraInfo> l_QListQCameraInfo_available_cameras =
      QCameraInfo::availableCameras();
  if (l_QListQCameraInfo_available_cameras.length() > 2) {
    m_QCamera_required_camera =
        new QCamera(l_QListQCameraInfo_available_cameras[1]);
  } else
    m_QCamera_required_camera =
        new QCamera(l_QListQCameraInfo_available_cameras[0]);

  QCameraViewfinder *mCameraViewfinder = new QCameraViewfinder(this);
  m_QCamera_required_camera->setViewfinder(mCameraViewfinder);

  m_QCamera_required_camera->start();

  layout->addWidget(m_QPushButton_calibration);
  layout->addWidget(mCameraViewfinder);
}

MainWindow::~MainWindow() {}

void MainWindow::handleButton() {}
