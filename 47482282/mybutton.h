#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QMouseEvent>
#include <QPushButton>
#include <QDebug>

class MyButton : public QPushButton
{
 Q_OBJECT

public:
    MyButton(QWidget *parent = Q_NULLPTR):QPushButton(parent){

    }

protected:
    void mousePressEvent(QMouseEvent *e) {
        if(e->button()==Qt::RightButton) {
            emit btnRightClicked();
            qDebug() << "Emitted";
        }
    }

signals:
    void btnRightClicked();
};
#endif // MYBUTTON_H
