#include "syntaxhighlighter.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  qmlRegisterType<SyntaxHighlighterHelper>("Foo", 1, 0,
                                           "SyntaxHighlighterHelper");
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
