#include <QGeoCircle>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include <random>

class CircleController : public QObject {
  Q_OBJECT
  Q_PROPERTY(QGeoCoordinate center READ center NOTIFY centerChanged)
  Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
public:
  CircleController(QObject *parent = 0) : QObject(parent) {
    mCircle.setRadius(1000);
  }
  void setCenter(const QGeoCoordinate &center) {
    if (mCircle.center() == center)
      return;
    mCircle.setCenter(center);
    emit centerChanged();
  }
  QGeoCoordinate center() const { return mCircle.center(); }

  void translate(double degreesLatitude, double degreesLongitude) {
    mCircle.translate(degreesLatitude, degreesLongitude);
    emit centerChanged();
  }

  qreal radius() const { return mCircle.radius(); }
  void setRadius(const qreal &radius) {
    if (mCircle.radius() == radius)
      return;
    mCircle.setRadius(radius);
    emit radiusChanged();
  }
signals:
  void centerChanged();
  void radiusChanged();

private:
  QGeoCircle mCircle;
};

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QGuiApplication app(argc, argv);
  CircleController circleController;
  circleController.setCenter(QGeoCoordinate(56.006355, 92.860984));
  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&circleController]() {
    // emulate displacement of the circle
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(-0.05, 0.05);
    circleController.translate(dis(e), dis(e));
  });
  timer.start(1000);
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("circleController",
                                           &circleController);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}

#include "main.moc"
