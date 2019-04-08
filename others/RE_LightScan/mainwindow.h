#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lsplot.h"
#include <QMainWindow>
#include <qwt_plot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  LSPlot *plot = new LSPlot(QString(), Qt::white);
  Ui::MainWindow *ui;
  bool isZoomingActived;
  bool isGrabActived;
  bool disableAll();

private slots:
  void zooming();
  void grab();
  void autoScale();
  void reinitialScale();
};

#endif // MAINWINDOW_H
