#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "serialport.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  qmlRegisterType<SerialPort>("SerialPortLib", 1, 0, "SerialPort");

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
