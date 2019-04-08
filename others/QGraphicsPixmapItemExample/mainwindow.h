#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphicspixmapitem.h"
#include "graphicsscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_actionOpen_triggered();
  void onNewPixmap(const QPixmap pixmap);

private:
  Ui::MainWindow *ui;

  GraphicsPixmapItem *item;
  GraphicsScene *scene;

  QPixmap original_pixmap;
  QPixmap new_pixmap;
};

#endif // MAINWINDOW_H
