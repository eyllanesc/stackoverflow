#include "airportsmodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);

  AirportsModel apModel;
  Airport KORD =
      Airport("KORD", "CHICAGO O'HARE INTL", 41.97732, -87.90801, 680);
  KORD.addRunway(Runway("04L", 42, 41.98166, -87.91392, 656));
  KORD.addRunway(Runway("22R", 222, 41.99754, -87.89637, 648));

  apModel.addAirport(KORD);

  QQmlApplicationEngine engine;

  engine.rootContext()->setContextProperty("airportsModel", &apModel);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
