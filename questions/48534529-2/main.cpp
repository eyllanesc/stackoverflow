#include "filemanager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);
  qmlRegisterType<FileManager>("com.eyllanesc.filemanager", 1, 0,
                               "FileManager");
  qmlRegisterType<File>("com.eyllanesc.filemanager", 1, 0, "File");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
