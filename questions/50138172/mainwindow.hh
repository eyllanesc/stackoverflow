#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>

class GameBoard;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(GameBoard &board, QWidget *parent = 0);
    ~MainWindow();
private:
    QGraphicsView m_view{this};
};

#endif // MAINWINDOW_H
