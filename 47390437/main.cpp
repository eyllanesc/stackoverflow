#include "navaidsmodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    NavaidsModel model;
    model.readFromCSV(":/files/data.csv");

    model.addNavaidsPoint(NavaidsPoint("Oslo", 59.9154, 10.7425, "NG"));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("navaidsModel", &model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
