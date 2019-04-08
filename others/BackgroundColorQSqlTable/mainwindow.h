#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class QSqlRelationalDelegate;
class SqlRelationalTableModel;
class QSqlTableModel;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;

  QSqlDatabase db;

  QSqlRelationalDelegate *delegate;
  SqlRelationalTableModel *modelUser;
  QSqlTableModel *modelCity;

  void loadDb(QString path);
};

#endif // MAINWINDOW_H
