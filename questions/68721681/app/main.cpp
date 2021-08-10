#include "foointerface.h"

#include <QDir>
#include <QGuiApplication>
#include <QPluginLoader>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QTranslator>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QTranslator appTranslator;
    qDebug() << "appTranslator Loaded?:" << appTranslator.load(":/languages/app.qm");

    QTranslator pluginTranslator;
    qDebug() << "pluginTranslator Loaded?:" << pluginTranslator.load(":/languages/plugin.qm");

    FooInterface *fooInterface = nullptr;

    QDir pluginsDir(QCoreApplication::applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");
    const QStringList entries = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entries) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            fooInterface = qobject_cast<FooInterface *>(plugin);
            if (fooInterface)
                break;
            pluginLoader.unload();
        }
    }

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [fooInterface](){
        qDebug() << fooInterface->print();
    });
    timer.start(1000);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QTimer::singleShot(1000, &engine, [&](){
        QCoreApplication::instance()->installTranslator(&appTranslator);
        QCoreApplication::instance()->installTranslator(&pluginTranslator);
        engine.retranslate();
    });

    return app.exec();
}
