#include "mycombobox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyComboBox combo;
    combo.setDataForCompleter(combo.createTestData());
    combo.show();
    return a.exec();
}
