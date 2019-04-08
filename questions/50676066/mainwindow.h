#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsPixmapItem;
class QGraphicsView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  bool eventFilter(QObject *watched, QEvent *event);

private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  QGraphicsPixmapItem *player;
  QGraphicsView *view;
};

#endif // MAINWINDOW_H
