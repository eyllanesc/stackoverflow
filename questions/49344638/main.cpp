#include "markermodel.h"

#include <QApplication>
#include <QQmlContext>
#include <QQuickWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QQuickWidget w;
  MarkerModel model;
  w.rootContext()->setContextProperty("markerModel", &model);
  w.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
  w.show();

  return a.exec();
}
