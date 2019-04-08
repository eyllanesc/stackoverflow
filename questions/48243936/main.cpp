#include "singletonbaseclass.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  qmlRegisterType<SingletonBaseClass>("SingletonBaseClass", 1, 0,
                                      "SingletonBaseClass");
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty())
    return -1;

  qDebug() << SingletonBaseClass::instance(&engine);

  return app.exec();
}
