#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>

static bool createConnection() {

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("empdb.db");
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
  return true;
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  if (!createConnection()) {
    return -1;
  }
  MainWindow w;
  w.resize(640, 480);
  w.show();

  return a.exec();
}
