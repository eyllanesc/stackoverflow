#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QBoxLayout>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  QGraphicsView *view;
  QGraphicsRectItem *boundRec;
};

#endif // MAINWINDOW_H
