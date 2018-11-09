#include "gameboard.hh"
#include "mainwindow.hh"

MainWindow::MainWindow(GameBoard &board, QWidget *parent)
    : QMainWindow( parent)
{
    m_view.setScene(&board);
    setCentralWidget(&m_view);
    setMinimumHeight(HEIGHT*GRID_SIDE + GRID_SIDE);
    setMinimumWidth(WIDTH*GRID_SIDE + GRID_SIDE);
}

MainWindow::~MainWindow()
{

}
