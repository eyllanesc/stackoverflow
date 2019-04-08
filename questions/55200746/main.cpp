#include "foomodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);
  FooModel model;
  model.append(Foo{"name1", QRect{0, 0, 100, 100}, QColor{"red"}});
  model.append(Foo{"name2", QRect{50, 50, 200, 300}, QColor{"green"}});
  model.append(Foo{"name3", QRect{300, 200, 40, 60}, QColor{"blue"}});
  model.append(Foo{"name4", QRect{500, 500, 50, 70}, QColor{"yellow"}});
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("sourcemodel", &model);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
