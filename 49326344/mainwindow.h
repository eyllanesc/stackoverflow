#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsTextItem;
class QGraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static MainWindow *instance(QWidget* parent = 0);
    ~MainWindow();
    void drawConnection();
    static MainWindow* mInstance;
private:
    MainWindow(QWidget *parent = 0);
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QGraphicsTextItem *connection;
};

#endif // MAINWINDOW_H
