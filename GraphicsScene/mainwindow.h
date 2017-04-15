#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphicsscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onChangedMousePosition(QPointF point);


private:
    Ui::MainWindow *ui;

    GraphicsScene* scene;
};

#endif // MAINWINDOW_H
