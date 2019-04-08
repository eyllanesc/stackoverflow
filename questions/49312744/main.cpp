#include <QApplication>
#include <QUrl>
#include <QWebEngineView>

class WebEnginePage : public QWebEnginePage {
  Q_OBJECT
public:
  WebEnginePage(QObject *parent = Q_NULLPTR) : QWebEnginePage(parent) {
    connect(this, &WebEnginePage::featurePermissionRequested, this,
            &WebEnginePage::onFeaturePermissionRequested);
  }
private Q_SLOTS:
  void onFeaturePermissionRequested(const QUrl &securityOrigin,
                                    QWebEnginePage::Feature feature) {

    if (feature == QWebEnginePage::MediaAudioCapture ||
        feature == QWebEnginePage::MediaVideoCapture ||
        feature == QWebEnginePage::MediaAudioVideoCapture)
      setFeaturePermission(securityOrigin, feature,
                           QWebEnginePage::PermissionGrantedByUser);
    else
      setFeaturePermission(securityOrigin, feature,
                           QWebEnginePage::PermissionDeniedByUser);
  }
};

QUrl commandLineUrlArgument() {
  const QStringList args = QCoreApplication::arguments();
  for (const QString &arg : args.mid(1)) {
    if (!arg.startsWith(QLatin1Char('-')))
      return QUrl::fromUserInput(arg);
  }
  return QUrl(QStringLiteral("https://www.qt.io"));
}

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);
  QWebEngineView view;
  view.setPage(new WebEnginePage);
  view.setUrl(commandLineUrlArgument());
  view.resize(1024, 750);
  view.show();

  return app.exec();
}

#include "main.moc"
