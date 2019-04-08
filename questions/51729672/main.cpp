#include "domainmanager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

static QObject *domain_provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
  Q_UNUSED(engine)
  Q_UNUSED(scriptEngine)

  DomainManager *example = new DomainManager;
  return example;
}

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  qmlRegisterSingletonType<DomainManager>("my.pkg", 1, 0, "DomainManager",
                                          domain_provider);
  qmlRegisterUncreatableType<Control>("my.pkg", 1, 0, "Control",
                                      "Get it fresh from DomainManager");

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
