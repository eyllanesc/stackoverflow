#include "login.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Login l;
    //l.createConnection();
    MainWindow w;
    l.show();
    QObject::connect(&l, &Login::accept, [&w](const User user){
        w.setUser(user);
        w.show();
    });
    QObject::connect(&w, SIGNAL(Logout()), &l, SLOT(show()));
    return a.exec();
}
