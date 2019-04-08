#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QParallelAnimationGroup>

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
  QParallelAnimationGroup *group;
};

#endif // MAINWINDOW_H
