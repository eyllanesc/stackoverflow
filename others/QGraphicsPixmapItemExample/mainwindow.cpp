#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  scene = new GraphicsScene(this);
  ui->preview->setScene(scene);
  item = new GraphicsPixmapItem;
  /*ui->preview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->preview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);*/
  scene->addItem(item);
  connect(item, &GraphicsPixmapItem::newPixmap, this, &MainWindow::onNewPixmap);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_triggered() {

  QString path = QDir::homePath();
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open Background"), path,

      tr("Images (*.png *.bmp *.jpg *.jpeg);;All files (*.*)"));

  original_pixmap = QPixmap(filename);
  item->setPixmap(original_pixmap);
}

void MainWindow::onNewPixmap(const QPixmap pixmap) {

  new_pixmap = pixmap;
  QFile file("new_file.png");
  file.open(QIODevice::WriteOnly);
  new_pixmap.save(&file, "PNG");
}
