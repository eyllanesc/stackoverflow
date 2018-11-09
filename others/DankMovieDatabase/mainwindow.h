#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "moviescreen.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void sendRequest();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    MovieScreen moviescreen;
};

#endif // MAINWINDOW_H
