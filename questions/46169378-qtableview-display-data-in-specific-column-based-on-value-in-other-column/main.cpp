#include "dialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QSqlQuery>


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.exec("create table TableExample (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
               "Field1 varchar(20), position INTEGER, Field2 varchar(20), state varchar(20), Field3 varchar(20))");

    query.exec("insert INTO TableExample (Field1, position, Field2, state, Field3) values('Danny', 3. 'Young', 'A', 'aaa')");
    query.exec("insert INTO TableExample (Field1, position, Field2, state, Field3) values('Christine', 4,  'Holand', 'B', 'bbb')");
    query.exec("insert INTO TableExample (Field1, position, Field2, state, Field3) values('Lars', 1, 'Gordon', 'C', 'ccc')");
    query.exec("insert INTO TableExample (Field1, position, Field2, state, Field3) values('Roberto', 5, 'Robitaille', 'D', 'ddd')");
    query.exec("insert INTO TableExample (Field1, position, Field2, state, Field3) values('Maria', 2, 'Papadopoulos', 'E', 'eee')");

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection())
            return 1;
    Dialog w;
    w.show();

    return a.exec();
}
