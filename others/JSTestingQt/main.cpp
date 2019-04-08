#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <qtwebengineglobal.h>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  QtWebEngine::initialize();

  QQmlApplicationEngine engine;
  engine.load(QUrl(QLatin1String("qrc:/main.qml")));

  return app.exec();
}
