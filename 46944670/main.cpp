#include "positionwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PositionWidget w;
    w.show();

    return a.exec();
}
