#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QObject>

class Helper : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QString getClassName(QObject *obj) const{
           return obj? obj->metaObject()->className(): "";
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    Helper helper;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("helper", &helper);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
