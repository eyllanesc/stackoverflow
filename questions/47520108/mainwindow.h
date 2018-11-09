#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "car.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void Drive();
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    Car *fCar;
};

#endif // MAINWINDOW_H
