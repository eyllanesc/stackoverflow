#include "data.h"
#include "mymodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  qmlRegisterType<MyModel>("Model", 1, 0, "MyModel");
  qmlRegisterUncreatableType<Data>(
      "Model", 1, 0, "Data",
      QStringLiteral("Data should not be created in QML"));

  Data data;
  engine.rootContext()->setContextProperty(QStringLiteral("info"), &data);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
