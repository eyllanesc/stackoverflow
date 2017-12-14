#include "limits_t.h"
#include "splitdialgauge.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    qmlRegisterType<SplitDialGauge>("EngineModule", 1, 0, "SplitBarGauge");
    qmlRegisterType<LIMITS_T>("EngineModule", 1, 0, "Limits");
    //qRegisterMetaType<LIMITS_T>();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
