#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <osc_receiver.h>
#include <osc_sender.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<OSCReceiver>("OSC", 1, 0, "OSCReceiver");
    qmlRegisterType<OSCSender>("OSC", 1, 0, "OSCSender");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}