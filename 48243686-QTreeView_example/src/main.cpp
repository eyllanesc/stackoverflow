#include <QApplication>
#include "QMainWidget.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    QMainWidget mw;
    mw.show();
    return app.exec();
}
