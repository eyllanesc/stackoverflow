#include "mainwindow.h"
#include "mybutton.h"

#include <QGridLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *mWidget = new QWidget(this);
    QGridLayout *gLayout = new QGridLayout(mWidget);
    for(int i = 0; i < 5; i++) {
        MyButton *btn = new MyButton(mWidget);
        gLayout->addWidget(btn, 0, i);
        connect(btn, &MyButton::btnRightClicked, this, &MainWindow::onRightClicked);
        mButtons << btn;
    }

    mWidget->setLayout(gLayout);
    setCentralWidget(mWidget);

}

MainWindow::~MainWindow()
{
}

void MainWindow::onRightClicked()
{
    qDebug() << "clicked";
}
