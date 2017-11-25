#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mybutton.h"

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
    void onRightClicked();

private:
    QVector<MyButton *> mButtons;
};

#endif // MAINWINDOW_H
