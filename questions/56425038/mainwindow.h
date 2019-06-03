#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "markermodel.h"

#include <QGeoCoordinate>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private Q_SLOTS:
    void onTimeout();
private:
    Ui::MainWindow *ui;
    MarkerModel marker_model;
    int i = 0;
};

#endif // MAINWINDOW_H
