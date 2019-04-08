#include "translator.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setOrganizationName("Translations INC");
  QCoreApplication::setOrganizationDomain("translations.com");

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  Translator trans(&engine);
  engine.rootContext()->setContextProperty("trans", &trans);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
