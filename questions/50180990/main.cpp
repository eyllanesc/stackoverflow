#include <QApplication>
#include <QFileDialog>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QtWebEngine>

class DownloadHelper : public QObject {
  Q_OBJECT
public:
  Q_INVOKABLE void onDownloadRequested(QObject *download) {
    const QString &old_path = download->property("path").toString();
    const QString &suffix = QFileInfo(old_path).suffix();
    const QString &path = QFileDialog::getSaveFileName(nullptr, "Save File",
                                                       old_path, "*." + suffix);
    if (!path.isEmpty()) {
      download->setProperty("path", path);
      Q_ASSERT(QMetaObject::invokeMethod(download, "accept"));
    }
  }
};

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);
  QtWebEngine::initialize();

  QQmlApplicationEngine engine;
  DownloadHelper helper;
  engine.rootContext()->setContextProperty("downloadHelper", &helper);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}

#include "main.moc"
