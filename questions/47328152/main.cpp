#include "trackwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrackWindow w;
    w.show();

    return a.exec();
}
