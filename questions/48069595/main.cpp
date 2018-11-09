#include "maincpp.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

static QObject *singletonTypeProvider(QQmlEngine *, QJSEngine *)
{
    return Config::getInstance();
}

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    qmlRegisterSingletonType<Config>("Config", 1, 0, "Config", singletonTypeProvider);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("MainCpp"), new MainCpp());
    //engine.rootContext()->setContextProperty(QStringLiteral("Config"), new Config());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
