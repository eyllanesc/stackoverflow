#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();
  void onManagerFinished(QNetworkReply *reply);

private:
  Ui::MainWindow *ui;
  QNetworkAccessManager manager;
};

#endif // MAINWINDOW_H
