#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QLineEdit>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->leUrl->setText("http://rfm-live-mp3-64.scdn.arkena.com/rfm.mp3");
  ui->leOutput->setText(
      QDir(qApp->applicationDirPath()).absoluteFilePath("test.mp3"));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
  mDs << reply->readAll();
  qDebug() << bytesReceived << bytesTotal;
}

void MainWindow::on_selectButton_clicked() {
  QString filename =
      QFileDialog::getSaveFileName(this, "Select ", qApp->applicationDirPath());
  ui->leOutput->setText(filename);
}

void MainWindow::on_startButton_clicked() {

  mFile.setFileName(ui->leOutput->text());

  mDs.setDevice(&mFile);

  if (!mFile.open(QFile::WriteOnly))
    return;

  QNetworkRequest request(QUrl(ui->leUrl->text()));

  reply = mNam.get(request);
  connect(reply, &QNetworkReply::downloadProgress, this,
          &MainWindow::onDownloadProgress);
}

void MainWindow::on_pushButton_clicked() {
  if (reply) {
    reply->disconnect(SIGNAL(downloadProgress(qint64, qint64)));
    reply->abort();
    mFile.close();
    reply->deleteLater();
  }
}
