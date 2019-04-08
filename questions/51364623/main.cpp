#include "itemfiltersortmodel.h"
#include "itemmodel.h"
#include "samplemanager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QTime>
#include <QTimer>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  SampleManager manager;
  manager.setModel(new ItemModel);

  // test
  QTime now = QTime::currentTime();
  for (int i = 0; i < 20; ++i) {
    manager.model()->appendItem(new Item(now.addSecs(i).toString()));
  }

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("manager", &manager);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
