#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <pdfModel.h>

int main(int argc, char *argv[]) {
  /// enable debug
  qputenv("POPPLERPLUGIN_DEBUG", "1");
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  qmlRegisterType<PdfModel>("org.docviewer.poppler", 1, 0, "Poppler");
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
