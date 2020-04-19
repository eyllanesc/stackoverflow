#include "mapmarker.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //Added for model registration
    QQmlApplicationEngine engine;


    qmlRegisterType<MarkerModel>("MarkerModel", 1, 0, "MarkerModel");

    engine.load(QUrl(QStringLiteral("qrc:/mainWindow.qml")));

    return app.exec();
}
