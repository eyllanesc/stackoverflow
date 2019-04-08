#include <QDir>
#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>
#include <QtWebView>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);
  QtWebView::initialize();

  QQmlApplicationEngine engine;

  /*QString html;
  QFile mFile(":/index.html");

  if(mFile.open(QFile::ReadOnly | QFile::Text)){
      html = QString(mFile.readAll());
  }
  mFile.close();
  engine.rootContext()->setContextProperty("htmlText",
  QVariant::fromValue(html));*/
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
