#include "backend.h"
#include "custom_class.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

void register_Qml_types() {
  qmlRegisterType<Backend>("customApi", 1, 0, "Backend");
  qmlRegisterType<CustomClass>("customApi", 1, 0, "CustomClass");
}

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  register_Qml_types();
  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:/main.qml"));

  return app.exec();
}
