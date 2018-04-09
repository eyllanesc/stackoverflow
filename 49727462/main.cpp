#include "assetlistmodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    AssetListModel model;
    QGeoCoordinate coord(41.97732, -87.90801);
     model.addAsset(coord, "testing_name1");
     model.addAsset(coord, "testing_name2");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("assetmodel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
