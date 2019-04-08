#include "connectudp.h"
#include "datasourceobject.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  /*init of GUI*/
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  qmlRegisterType<ConnectUdp>("com.powertune", 2, 0, "ConnectUdpObject");

  QGuiApplication app(argc, argv);
  app.setOrganizationName("Power-Tune");
  app.setOrganizationDomain("power-tune.org");
  app.setApplicationName("PowerTune 2");

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("ConnectUdp",
                                           new ConnectUdp(&engine));
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
