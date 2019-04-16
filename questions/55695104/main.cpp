#include "datasourcemodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include <QRandomGenerator>
#include <random>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    std::uniform_real_distribution<double> dist(0.0, 10.0);
    DataSourceModel model;
    for (int i=0; i<100;i++) {
        model.addDataSourceObject(DataSourceObject{i,
                                                   QString::number(i),
                                                   "",
                                                   dist(*QRandomGenerator::global())
                                  });
    }
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataSourceModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&model, &dist](){
        QModelIndex ix = model.index(88);
        model.setData(ix, dist(*QRandomGenerator::global()), DataSourceModel::valueRole);
    });
    timer.start(1000);
    return app.exec();
}
