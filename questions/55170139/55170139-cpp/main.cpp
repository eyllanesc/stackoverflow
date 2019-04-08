#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebView>

class PDFJS : public QObject {
  Q_OBJECT
  Q_PROPERTY(
      QString version READ version WRITE setVersion NOTIFY versionChanged)
  QString m_version;

public:
  QString version() const { return m_version; }
  void setVersion(QString version) {
    if (m_version == version)
      return;
    m_version = version;
    Q_EMIT versionChanged(m_version);
  }
  Q_SIGNAL void versionChanged(QString version);
  Q_INVOKABLE QUrl getUrl(const QUrl &path) {
    QString pdfjs_path = QDir::current().filePath(
        QString("3rdParty/pdfjs-%1-dist/web/viewer.html").arg(m_version));
    QUrl pdf_url = QUrl::fromLocalFile(pdfjs_path);
    QUrlQuery query;
    query.addQueryItem("file", path.toString());
    pdf_url.setQuery(query);
    return pdf_url;
  }
};

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);
  QtWebView::initialize();
  QQmlApplicationEngine engine;
  PDFJS pdfjs;
  engine.rootContext()->setContextProperty(
      "applicationDirPath", QGuiApplication::applicationDirPath());
  engine.rootContext()->setContextProperty("PDFJS", &pdfjs);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
#include "main.moc"
