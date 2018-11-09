#include "dialog.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

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

    const QString tablename = "TableTest";

    //data of http://peric.github.io/GetCountries/
    QFile file(":/all.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return 1;
    }

    QStringList headers = QString(file.readLine()).trimmed()
            .replace('-', '_')
            .replace(QString("\""),QString("")).split(",");
    QSqlQuery query;
    QString str = QString("create table %1 (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT").arg(tablename);
    for(QString header: headers){
        str += QString(",%1 VARCHAR(20)").arg(header);
    }
    str += ")";
    query.exec(str);

    QString insert = QString("insert into %1(").arg(tablename);
    for(const QString header: headers){
        insert += header+",";
    }
    insert.chop(1);
    insert += ") values (";
    for(int i=0; i < headers.count(); i++){
        insert += QString(" '%%1',").arg(i+1);
    }
    insert.chop(1);
    insert += ")";
    while (!file.atEnd()) {
        QString line = insert;
        for(QString col:  QString(file.readLine()).trimmed().split("\",")){
            line = line.arg(col.replace(QString("\""), QString("")));
        }
        query.exec(line);
    }
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
