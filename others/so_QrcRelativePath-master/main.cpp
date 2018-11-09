#include "View.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication qtapp(argc, argv);

    View view;
    view.show();

    /*
     * Run the app
     */
    return qtapp.exec();
}

