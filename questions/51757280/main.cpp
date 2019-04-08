#include "visualizationoptions.h"
#include "vizfactory.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  qmlRegisterUncreatableType<VisualizationOptions>(
      "Wormhole", 1, 0, "VisualizationOptions",
      QString("Cannot create abstract class VisualizationOptions"));

  qmlRegisterType<LayoutOptions>("Wormhole", 1, 0, "LayoutOptions");
  qmlRegisterType<FooOptions>("Wormhole", 1, 0, "FooOptions");
  qmlRegisterType<VizFactory>("Wormhole", 1, 0, "VizFactory");

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
