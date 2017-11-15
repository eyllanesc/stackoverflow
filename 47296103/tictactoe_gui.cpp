#include "tictactoe_gui.h"

#include <QButtonGroup>
#include <QGridLayout>
#include <QToolButton>

#include <QtConcurrent>

#include <QDebug>

TicTacToe_Gui::TicTacToe_Gui(QWidget *parent) :
    QMainWindow(parent)
{
    setCentralWidget(new QWidget);
    QGridLayout *lay = new QGridLayout(centralWidget());
    group = new QButtonGroup(this);
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){
            board[i][j] = TicTacToe_State::N;
            QToolButton *btn = new QToolButton(this);
            btn->setFixedSize(100, 100);
            btn->setStyleSheet("QToolButton::disabled{color:black}");
            group->addButton(btn, 3*i+j);
            lay->addWidget(btn, i , j);
        }
    }
    connect(group, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &TicTacToe_Gui::onClicked);
    isFinished = false;
}

TicTacToe_Gui::~TicTacToe_Gui()
{

}

void TicTacToe_Gui::setDisabledButtons(bool enable)
{
    for(QAbstractButton *btn: group->buttons()){
        btn->setDisabled(enable);
    }
}

void TicTacToe_Gui::onClicked(int id)
{

    setDisabledButtons(true);
    if(!isFinished){
        QAbstractButton *btnO = group->button(id);
        btnO->setText("O");
        int row = id/3;
        int col = id%3;
        board[row][col] = TicTacToe_State::O;
        group->removeButton(btnO);
    }

    isFinished = group->buttons().size() == 0;

    if(!isFinished){
        QFutureWatcher<TicTacToe_Result> watcher;
        QFuture<TicTacToe_Result> future = QtConcurrent::run([&](){
            for(int i=0; i < 3; i++){
                for(int j=0; j < 3; j++){
                    QString text;
                    switch (board[i][j]) {
                    case TicTacToe_State::N:
                        text = "NONE";
                        break;
                    case TicTacToe_State::X:
                        text = "X";
                        break;
                    case TicTacToe_State::O:
                        text = "0";
                        break;
                    }
                    qDebug()<<i<<j<<text;
                }
            }

            for(int i=0; i<=1000000000; i++){
               ;
            }

            TicTacToe_State s = TicTacToe_State::N;
            int r, c;
            do{
                r = qrand()%3;
                c = qrand()%3;
                s = board[r][c];
            }
            while (s!= TicTacToe_State::N);
            qDebug()<<"finish processing";
            return TicTacToe_Result{r, c};
        });

        watcher.setFuture(future);
        QEventLoop loop;
        connect(&watcher, &QFutureWatcherBase::finished, &loop, &QEventLoop::quit);
        loop.exec();

        TicTacToe_Result r = watcher.result();
        board[r.row][r.col] = TicTacToe_State::X;

        QAbstractButton *btnX = group->button(3*r.row+r.col);
        btnX->setText("X");
        group->removeButton(btnX);
        isFinished = group->buttons().size() == 0;
    }
    setDisabledButtons(false);
}
