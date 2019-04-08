#include <QApplication>
#include <QDateTime>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardItemModel>

int main(int argc, char *argv[]) {
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

  QApplication app(argc, argv);

  QStandardItemModel lineModel(100, 3); // 100 rows and 3 columns

  for (int row = 0; row < lineModel.rowCount(); row++) {
    QStandardItem *item1 = new QStandardItem(QString::number(row));
    QDateTime time = QDateTime::currentDateTime().addSecs(row);
    QStandardItem *item2 =
        new QStandardItem(QString::number(time.toMSecsSinceEpoch()));
    QStandardItem *item3 = new QStandardItem(QString::number(row * row));
    lineModel.setItem(row, 0, item1);
    lineModel.setItem(row, 1, item2);
    lineModel.setItem(row, 2, item3);
  }

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("lineModel", &lineModel);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
