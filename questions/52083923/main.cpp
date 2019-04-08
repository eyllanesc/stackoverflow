#include "currency.h"
#include "factory.h"
#include "money.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  qmlRegisterUncreatableType<Currency>("test", 1, 0, "Currency", "error");
  qmlRegisterUncreatableType<Money>("test", 1, 0, "Money", "error");
  qmlRegisterSingletonType<Factory>(
      "test", 1, 0, "Factory",
      [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(scriptEngine)

        Factory *instance = Factory::instance();
        engine->setObjectOwnership(instance,
                                   QQmlEngine::ObjectOwnership::CppOwnership);

        return instance;
      });

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
