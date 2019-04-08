#include "interfacageqml.h"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

static QObject *singletonTypeProvider(QQmlEngine *, QJSEngine *) {
  return interfacageQML::getInstance();
}

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  qmlRegisterSingletonType<interfacageQML>(
      "Interfacage", 1, 0, "InterfacageQML", singletonTypeProvider);

  interfacageQML *obj =
      qobject_cast<interfacageQML *>(interfacageQML::getInstance());
  QObject::connect(obj, &interfacageQML::clicked,
                   [] { qDebug() << "clicked"; });
  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
