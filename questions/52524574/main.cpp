#include "connection.h"
#include "sqltablemodel.h"
#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  if (!createConnection())
    return -1;

  SqlTableModel model;
  model.setTable("Customer");
  model.select();

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("cppmodel", &model);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
