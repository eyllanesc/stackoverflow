#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GraphicsScene;
class QGraphicsItem;
class QGraphicsPixmapItem;

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
  GraphicsScene *scene;
};

#endif // MAINWINDOW_H
