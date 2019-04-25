#include "cbottom.h"
#include "cmiddle.h"
#include "ctop.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

static void registerMyQmlTypes() {
    qmlRegisterType<CBottom>("Bottom", 1, 0, "Bottom");
    qmlRegisterType<CMiddle>("Middle", 1, 0, "Middle");
    qmlRegisterType<CTop>("Top", 1, 0, "Top");
}
Q_COREAPP_STARTUP_FUNCTION(registerMyQmlTypes)

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QStringList middles;
    middles.append("FirstMiddle");
    middles.append("SecondMiddle");
    CTop top(middles);
    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("theTop", &top);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
