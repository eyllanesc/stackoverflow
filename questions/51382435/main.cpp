#include "itemfiltersortmodel.h"
#include "itemmodel.h"
#include "modelimageprovider.h"
#include "samplemanager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

static Item *create_item() {
  Item *it = new Item;
  QImage img(50, 50, QImage::Format_RGB32);
  img.fill(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  it->setPhoto(img);
  return it;
}

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  SampleManager manager;
  manager.setModel(new ItemModel);

  for (int i = 0; i < 10; ++i) {
    manager.model()->appendItem(create_item());
  }

  QTimer timer;

  QObject::connect(&timer, &QTimer::timeout, [&manager]() {
    manager.model()->appendItem(create_item());
  });
  timer.start(100);

  ModelImageProvider *provider = new ModelImageProvider(manager.filterModel());
  QQmlApplicationEngine engine;
  engine.addImageProvider("model", provider);
  engine.rootContext()->setContextProperty("manager", &manager);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
