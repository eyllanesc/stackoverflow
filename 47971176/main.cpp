#include "widget.h"
#include "worker.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget widget;
    widget.show();
    return a.exec();
}
