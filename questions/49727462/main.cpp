#include "assetlistmodel.h"
#include "nodemodel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include <random>

struct TestStruct {
  QGeoCoordinate coord;
  int angle;
};
static TestStruct append_random_coordinate() {
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::normal_distribution<> dist1(0, .1);
  std::uniform_int_distribution<> dist2(0, 360);
  return TestStruct{QGeoCoordinate(dist1(rng), dist1(rng)), dist2(rng)};
}

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  AssetListModel model;

  QGeoCoordinate center(41.97732, -87.90801);
  model.createAsset(center, QColor("red"), "testing_name1");
  model.createAsset(center, QColor("blue"), "testing_name2");

  QGeoCoordinate pos1{center};
  QGeoCoordinate pos2{center};
  QQmlApplicationEngine engine;
  model.register_objects("assetmodel", "nodemodel", engine.rootContext());
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&model, &pos1, &pos2]() {
    TestStruct t1 = append_random_coordinate();
    pos1 = QGeoCoordinate{t1.coord.latitude() + pos1.latitude(),
                          t1.coord.longitude() + pos1.longitude()};
    model.addAsset(pos1, t1.angle, "testing_name1");
    TestStruct t2 = append_random_coordinate();
    pos2 = QGeoCoordinate{t2.coord.latitude() + pos2.latitude(),
                          t2.coord.longitude() + pos2.longitude()};
    model.addAsset(pos2, t2.angle, "testing_name2");
  });
  timer.start(1000);

  return app.exec();
}
