#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QGraphicsView>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "mattoqimage.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_loadBtn_clicked() {

  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::currentPath(),
                                   tr("Image Files (*.png *.jpg *.bmp)"));
  if (filename.isEmpty())
    return;

  cv::Mat image = cv::imread(filename.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

  cv::Mat histEquImg;
  equalizeHist(image, histEquImg);

  QImage qimage = MatToQImage(histEquImg);
  QPixmap pixmap = QPixmap::fromImage(qimage);
  scene->addPixmap(pixmap);
  ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}
