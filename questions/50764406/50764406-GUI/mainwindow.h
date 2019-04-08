#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

  void on_selectButton_clicked();

  void on_startButton_clicked();

  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  QNetworkAccessManager mNam;
  QFile mFile;
  QDataStream mDs;
  QNetworkReply *reply;
};

#endif // MAINWINDOW_H
