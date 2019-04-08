#include "sqltrafficmodel.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

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
  if (!query.exec("create table traffic (date DATE default CURRENT_DATE,  sent "
                  "INTEGER, recv INTEGER)")) {
    qDebug() << query.lastError().text();
  }
  QTime time = QTime::currentTime();
  qsrand((uint)time.msec());

  QDate today = QDate::currentDate();
  for (int i = 0; i < 10; i++) {
    query.prepare("insert into traffic values(:date, :sent, :recv)");
    query.bindValue(":date", today.addDays(i));
    query.bindValue(":sent", qrand() % 1000);
    query.bindValue(":recv", qrand() % 1000);
    if (!query.exec()) {
      qDebug() << query.lastError().text();
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QApplication app(argc, argv);

  if (!createConnection())
    return -1;
  qmlRegisterType<SqlTrafficModel>("com.eyllanesc.models", 1, 0,
                                   "SqlTrafficModel");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
