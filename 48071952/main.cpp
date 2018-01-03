#include <QGeoPath>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

class PathController: public QObject{
    Q_OBJECT
    Q_PROPERTY(QGeoPath geopath READ geoPath WRITE setGeoPath NOTIFY geopathChanged)
public:
    PathController(QObject *parent=0):QObject(parent){}
    void test(){
        mGeoPath.addCoordinate(QGeoCoordinate(56.006355, 92.860984));
        mGeoPath.addCoordinate(QGeoCoordinate(56.1, 93));
        mGeoPath.addCoordinate(QGeoCoordinate(56.1, 92.777));
        QTimer *timer = new QTimer(this);

        QObject::connect(timer, &QTimer::timeout, [this](){
            mGeoPath.translate(0.001, -0.01);
            emit geopathChanged();
        });
        timer->start(1000);

    }
    QGeoPath geoPath() const{return mGeoPath;}
    void setGeoPath(const QGeoPath &geoPath){
        if(geoPath == mGeoPath)
            return;
        mGeoPath = geoPath;
        emit geopathChanged();
    }

signals:
    void geopathChanged();
private:
    QGeoPath mGeoPath;
};

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    PathController controller;
    controller.test();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("pathController", &controller);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}

#include "main.moc"
