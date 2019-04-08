#include "filtro.h"
#include "modello.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  modello mioModello;
  // riempio il modello
  for (int i = 0; i < 10; i++) {
    mioModello.addRicetta("Pane", "red", 5, false);
    mioModello.addRicetta("Branzino", "orange", 3, true);
  }

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&mioModello]() {
    mioModello.addRicetta("AAAA", "orange", 5, true);
  });
  timer.start(1000);

  Filtro filtroSuModello;
  filtroSuModello.setSourceModel(&mioModello);
  filtroSuModello.setFilterRole(mioModello.NomeRicetta);

  engine.rootContext()->setContextProperty("myModelFiltrato", &filtroSuModello);
  engine.rootContext()->setContextProperty("myModel", &mioModello);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
