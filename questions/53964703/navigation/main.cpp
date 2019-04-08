#include "sqlquerymodel.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>

static bool createConnection(const QString &path) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path);
  if (!db.open()) {
    qDebug() << "Cannot open database\n"
                "Unable to establish a database connection.\n"
                "This example needs SQLite support. Please read "
                "the Qt SQL driver documentation for information how "
                "to build it.\n\n"
                "Click Cancel to exit.";
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName("Navigation");
  QCoreApplication::setOrganizationDomain("www.navigation.com");
  QGuiApplication app(argc, argv);
  qmlRegisterType<SqlQueryModel>("SqlQueryModel", 1, 0, "SqlQueryModel");
  QQmlApplicationEngine engine;
  if (!createConnection("facharbeit.db"))
    return -1;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
