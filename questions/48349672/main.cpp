#include "configinterface.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);

  QList<QObject *> interfaces;

  for (int i = 0; i < 10; i++) {
    ConfigInterface *interface = new ConfigInterface;
    interface->setTag(QString("tag-%1").arg(i));
    interface->setDescription(QString("Description-%1").arg(i));
    interfaces << interface;
  }

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("myModel",
                                           QVariant::fromValue(interfaces));

  qDebug() << interfaces;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
