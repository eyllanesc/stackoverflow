#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QNetworkReply;
class QNetworkAccessManager;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void onResult(QNetworkReply *reply);

private:
  Ui::MainWindow *ui;

  QNetworkAccessManager *nam;
};

#endif // MAINWINDOW_H
