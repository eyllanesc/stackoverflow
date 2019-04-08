#include "datasourcemodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  DataSourceModel model;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("dataSourceModelObject", &model);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  QTimer timer;
  int counter = 0;

  QObject::connect(&timer, &QTimer::timeout, &model, [&counter, &model]() {
    QModelIndex ix = model.index(counter);
    model.setData(ix, 2 * ix.data(DataSourceModel::ValueRole).toInt(),
                  DataSourceModel::ValueRole);
    counter = (counter + 1) % (model.rowCount());
  });
  timer.start(100);

  return app.exec();
}
