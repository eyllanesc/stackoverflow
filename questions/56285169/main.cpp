#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextStream>
#include <QTimer>
#include <QGeoCoordinate>
#include <QRegularExpression>

class MarkerManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate position READ position NOTIFY positionChanged)
public:
    MarkerManager(QObject *parent=nullptr): QObject(parent){
        connect(&timer, &QTimer::timeout, this, &MarkerManager::readLine);
    }
    bool loadFile(const QString & filename, int interval=100){
        file.setFileName(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;
        ts.setDevice(&file);
        timer.start(interval);
        return true;
    }
    QGeoCoordinate position() const{
        return m_position;
    }
Q_SIGNALS:
    void positionChanged();
private Q_SLOTS:
    void readLine(){
        if(!ts.atEnd()){
            QString line = ts.readLine();
            QStringList elements = line.split(QRegularExpression("\\s+"));
            if(elements.count() == 2){
                bool ok1, ok2;
                double lat = elements[0].toDouble(&ok1);
                double lng = elements[1].toDouble(&ok2);
                if(ok1 && ok2){
                    m_position = QGeoCoordinate(lat, lng);
                    Q_EMIT positionChanged();
                }
            }
        }
    }
private:
    QFile file;
    QTextStream ts;
    QTimer timer;
    QGeoCoordinate m_position;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    MarkerManager manager;
    manager.loadFile("data_gps.txt");
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("manager", &manager);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
