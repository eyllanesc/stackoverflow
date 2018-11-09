#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tutowidget.h"

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

private:
    Ui::MainWindow *ui;
    TutoWidget *tuto;
};

#endif // MAINWINDOW_H
