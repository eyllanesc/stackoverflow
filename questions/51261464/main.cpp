#include "model.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  QVariantList modelist;

  for (int i = 0; i < 10; i++) {
    AnimalModel *model = new AnimalModel;
    model->addAnimal(Animal("Wolf", "Medium"));
    model->addAnimal(Animal("Polar bear", "Large"));
    model->addAnimal(Animal("Quoll", "Small"));
    modelist << QVariant::fromValue(model);
  }

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("modelist", modelist);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
