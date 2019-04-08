
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("/home/eyllanesc/test.db");
  if (!db.open()) {
    QMessageBox::critical(
        nullptr, QObject::tr("Cannot open database"),
        QObject::tr("Unable to establish a database connection.\n"
                    "This example needs SQLite support. Please read "
                    "the Qt SQL driver documentation for information how "
                    "to build it.\n\n"
                    "Click Cancel to exit."),
        QMessageBox::Cancel);
    return false;
  }

  QSqlQuery query;
  query.exec("CREATE TABLE IF NOT EXISTS person (id INTEGER PRIMARY KEY "
             "AUTOINCREMENT, "
             "firstname VARCHAR(20), lastname VARCHAR(20))");
  query.exec("insert into person values(101, 'Danny', 'Young')");
  query.exec("insert into person values(102, 'Christine', 'Holand')");
  query.exec("insert into person values(103, 'Lars', 'Gordon')");
  query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
  query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");

  return true;
}
//! [0]

#endif
