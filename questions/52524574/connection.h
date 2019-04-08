#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

static bool createConnection() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(":memory:");
  if (!db.open()) {
    qDebug() << "Cannot open database\n"
                "Unable to establish a database connection.\n"
                "This example needs SQLite support. Please read "
                "the Qt SQL driver documentation for information how "
                "to build it.\n\n"
                "Click Cancel to exit.";
    return false;
  }
  QSqlQuery query;
  if (!query.exec("CREATE TABLE Customer("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                  "name           TEXT    NOT NULL"
                  ")")) {
    qDebug() << query.lastError().text();
  }
  for (int i = 0; i < 10; i++) {
    query.prepare("insert into Customer(name) values(:name)");
    query.bindValue(":name", QString("name%1").arg(i + 1));
    if (!query.exec()) {
      qDebug() << query.lastError().text();
    }
  }
  return true;
}

#endif // CONNECTION_H
