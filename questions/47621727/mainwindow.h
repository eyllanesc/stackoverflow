#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "user.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void Logout();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUser(const User &user);
protected:
    void closeEvent(QCloseEvent *);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    User mUser;
};

#endif // MAINWINDOW_H
