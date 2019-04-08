#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>

#include <QDebug>

class Backend : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
  QString text() const { return mText; }
  void setText(const QString &text) {
    if (text == mText)
      return;
    mText = text;
    emit textChanged(mText);
  }
signals:
  void textChanged(const QString &text);

private:
  QString mText;
};

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  Backend backend;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("backend", &backend);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  // test

  QObject::connect(&backend, &Backend::textChanged,
                   [](const QString &text) { qDebug() << text; });
  return app.exec();
}

#include "main.moc"
