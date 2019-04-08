#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>

#include <QDebug>

static QPointF positionToAnotherItem(QQuickItem *source, QQuickItem *destine) {
  QPointF p = source->mapToScene(QPointF(0, 0));
  return destine->mapFromScene(p);
}

static QPointF positionToParent(QQuickItem *item) {
  return positionToAnotherItem(item, item->parentItem());
}

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine qml_engine;
  qml_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (qml_engine.rootObjects().isEmpty())
    return -1;

  QQuickItem *rectQuickItem =
      qml_engine.rootObjects()[0]->findChild<QQuickItem *>("rect_object");
  QQuickItem *rectQuickItemParent =
      qml_engine.rootObjects()[0]->findChild<QQuickItem *>(
          "rect_parent_object");

  QObject::connect(rectQuickItem, &QQuickItem::xChanged,
                   [rectQuickItem, rectQuickItemParent] {
                     qDebug() << positionToParent(rectQuickItem);
                     qDebug() << positionToAnotherItem(rectQuickItem,
                                                       rectQuickItemParent);
                   });

  QObject::connect(rectQuickItem, &QQuickItem::yChanged,
                   [rectQuickItem, rectQuickItemParent] {
                     qDebug() << positionToParent(rectQuickItem);
                     qDebug() << positionToAnotherItem(rectQuickItem,
                                                       rectQuickItemParent);
                   });

  return app.exec();
}
