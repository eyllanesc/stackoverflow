#include "dialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
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
    query.exec("create table person (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
               "firstname VARCHAR(20), lastname VARCHAR(20), country VARCHAR(20))");
    query.exec("insert into person (firstname, lastname, country) values('A', 'P', 'Peru')");
    query.exec("insert into person (firstname, lastname, country) values('B', 'Q', 'Brazil')");
    query.exec("insert into person (firstname, lastname, country) values('C', 'R', 'USA')");
    query.exec("insert into person (firstname, lastname, country) values('D', 'S', 'USA')");
    query.exec("insert into person (firstname, lastname, country) values('E', 'T', 'Brazil')");
    query.exec("insert into person (firstname, lastname, country) values('F', 'U', 'Peru')");
    query.exec("insert into person (firstname, lastname, country) values('G', 'V', 'Brazil')");
    query.exec("insert into person (firstname, lastname, country) values('H', 'W', 'USA')");
    query.exec("insert into person (firstname, lastname, country) values('I', 'X', 'USA')");
    query.exec("insert into person (firstname, lastname, country) values('J', 'Y', 'Brazil')");
    query.exec("insert into person (firstname, lastname, country) values('K', 'Z', 'Peru')");
    query.exec("insert into person (firstname, lastname, country) values('L', 'A', 'Brazil')");
    query.exec("insert into person (firstname, lastname, country) values('M', 'B', 'USA')");
    query.exec("insert into person (firstname, lastname, country) values('N', 'C', 'USA')");
    query.exec("insert into person (firstname, lastname, country) values('O', 'D', 'Brazil')");
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
