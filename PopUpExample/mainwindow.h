#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "popup.h"

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

    PopUp *popup;

    void movePopUp();

protected:
    void resizeEvent(QResizeEvent *event);
    void moveEvent(QMoveEvent *event);
};

#endif // MAINWINDOW_H
