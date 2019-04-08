#include "qjsonmodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QJsonModel model;
  std::string json = R"({
                       "firstName": "John",
                       "lastName": "Smith",
                       "age": 25,
                       "address":
                       {
                       "streetAddress": "21 2nd Street",
                       "city": "New York",
                       "state": "NY",
                       "postalCode": "10021"
                       },
                       "phoneNumber":
                       [
                       {
                       "type": "home",
                       "number": "212 555-1234"
                       },
                       {
                       "type": "fax",
                       "number": "646 555-4567"
                       }
                       ]
                       })";

  model.loadJson(QByteArray::fromStdString(json));

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("qjsonmodel", &model);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
