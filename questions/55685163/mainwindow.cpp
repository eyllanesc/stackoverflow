#include "mainwindow.h"
#include "pythonutils.h"

#include <QPushButton>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     button(new QPushButton)
{
    setCentralWidget(button);
    connect(button, &QPushButton::clicked, this, &MainWindow::onClicked);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onClicked()
{

   if(::PythonUtils::loadPlugins(QDir::current().absoluteFilePath("python-modules"), "plugin_loader", "iniciar"))
       qDebug()<< __PRETTY_FUNCTION__ << "successful";
}
