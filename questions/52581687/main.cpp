#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class SwipeManager : public QObject {
  Q_OBJECT
public:
  using QObject::QObject;
public slots:
  void moveToRight() { emit toRight(); }
  void moveToLeft() { emit toLeft(); }
signals:
  void toRight();
  void toLeft();
};

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);
  SwipeManager manager;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("manager", &manager);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  QWidget w;
  QPushButton left("to left");
  QPushButton right("to right");
  QHBoxLayout *lay = new QHBoxLayout(&w);
  lay->addWidget(&left);
  lay->addWidget(&right);
  QObject::connect(&left, &QPushButton::clicked, &manager,
                   &SwipeManager::moveToLeft);
  QObject::connect(&right, &QPushButton::clicked, &manager,
                   &SwipeManager::moveToRight);
  w.show();

  return app.exec();
}

#include "main.moc"
