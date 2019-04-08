#include "uidata.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QTimer>
#include <random>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(0, 100);

  QApplication app(argc, argv);
  UiData uiData;
  QTimer timer;

  static int counter = 0;
  QObject::connect(&timer, &QTimer::timeout, [&uiData, &uni, &rng]() {
    uiData.newData(counter, uni(rng));
    counter++;
  });
  timer.start(100);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("uiData", &uiData);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
