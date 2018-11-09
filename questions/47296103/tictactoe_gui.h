#ifndef TICTACTOE_GUI_H
#define TICTACTOE_GUI_H

#include <QMainWindow>

class QButtonGroup;

class TicTacToe_Gui : public QMainWindow
{
    Q_OBJECT
    enum TicTacToe_State{N, X, O};
    struct TicTacToe_Result
    {
        int row;
        int col;
    };
public:
    explicit TicTacToe_Gui(QWidget *parent = 0);
    ~TicTacToe_Gui();
private slots:
    void onClicked(int id);

private:
    QButtonGroup *group;
    void setDisabledButtons(bool enable);
    TicTacToe_State board[3][3];
    bool isFinished;
};

#endif // TICTACTOE_GUI_H
