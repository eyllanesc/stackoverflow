#include <QColor>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTime>
#include <QTimer>

class ColorProvider: public QObject{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:

    QColor color() const{
        return mColor;
    }
    void setColor(const QColor &color){
        if(color == mColor)
            return;
        mColor = color;
        emit colorChanged(mColor);
    }

    Q_INVOKABLE void randomColor(){
        qsrand((uint)QTime::currentTime().msec());
        setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
    }

signals:
    void colorChanged(const QColor &color);
private:
    QColor mColor;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    ColorProvider obj;

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &obj, &ColorProvider::randomColor);
    timer.start(100);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("colorProvider", &obj);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
