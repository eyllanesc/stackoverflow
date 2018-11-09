#include "tictactoe_gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicTacToe_Gui w;
    w.show();

    return a.exec();
}
