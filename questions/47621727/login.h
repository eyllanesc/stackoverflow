#ifndef LOGIN_H
#define LOGIN_H

#include "user.h"

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
signals:
    void accept(const User & user);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
