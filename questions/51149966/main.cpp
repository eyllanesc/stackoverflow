#include "samplemanager.h"
#include "samplemodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QTime>
#include <QTimer>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  SampleManager manager;
  manager.setModel(new SampleModel);

  // test
  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&manager]() {
    manager.model()->appendSample(new Sample(QTime::currentTime().toString()));
  });
  timer.start(1000);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("manager", &manager);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
