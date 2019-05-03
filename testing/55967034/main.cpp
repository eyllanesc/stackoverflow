#include "mycombobox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyComboBox combo;
    combo.show();
    return a.exec();
}
