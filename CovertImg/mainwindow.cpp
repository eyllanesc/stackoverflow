#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiSubWindow>
#include "imagewidget.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QtConcurrentRun>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mdi = new QMdiArea(this);
    setCentralWidget(mdi);
    mdi->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    connect(&watcher, &QFutureWatcherBase::finished,
            this, &MainWindow::onFinished);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::displayImage(const QImage &image, QString title){
    if(image.isNull()) return;
    QMdiSubWindow *subWindows = new QMdiSubWindow();
    subWindows->setAttribute(Qt::WA_DeleteOnClose);
    mdi->addSubWindow(subWindows);
    subWindows->setWindowTitle(title);
    ImageWidget *imgwidget = new ImageWidget();
    imgwidget->setImage(image); //
    subWindows->setWidget(imgwidget);
    subWindows->resize(image.size());
    subWindows->show();
}

void MainWindow::on_actionOpen_triggered()
{
    QString FileName=QFileDialog::getOpenFileName(this,"Open File","D:/imgDemo","*.* All Files;;*.bmp;;*.jpeg;;*.jpeg;;*.ppm;;*.png;;*.jpg");
    QImage image(FileName);
    displayImage(image,QFileInfo(FileName).fileName());
}

void MainWindow::on_actionOil_Paint_triggered()
{
    QMdiSubWindow *activeWindow = mdi->currentSubWindow();
    if(!activeWindow)
        return;
    ImageWidget *activeWidget = qobject_cast<ImageWidget*>(activeWindow->widget());
    QImage img_in =activeWidget->image();
    int intensity = QInputDialog::getInt(this,"",QString::fromUtf8("Please input Intensity Level"),3,1,100,1);
    int radius = QInputDialog::getInt(this,"",QString::fromUtf8("Please input Radius"),0,1,100,1);
    future =  QtConcurrent::run(ImageWidget::OilPaint, img_in, radius, intensity);
    watcher.setFuture(future);
}

void MainWindow::onFinished()
{
    displayImage(watcher.result(), " Oil Painting");
}
