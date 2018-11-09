#include "filestreewidget.h"

#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDialog w;
    w.setLayout(new QVBoxLayout);
    FilesTreeWidget tree;
    w.layout()->addWidget(&tree);
    w.show();
    return a.exec();
}
