#include "navaidsmodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    NavaidsModel model;
    model.addNavaidsPoint(NavaidsPoint(59.9154, 10.7425, NavaidsPoint::type1));
    model.addNavaidsPoint(NavaidsPoint(56.83348, 10.04158, NavaidsPoint::type2));
    model.addNavaidsPoint(NavaidsPoint(57.40642,11.83210, NavaidsPoint::type1));
    model.addNavaidsPoint(NavaidsPoint(55.67892,9.58512, NavaidsPoint::type2));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("navaidsModel", &model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
