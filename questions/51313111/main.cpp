#include <QGuiApplication>
#include <QJsonDocument>
#include <QQmlApplicationEngine>
#include <QWebChannelAbstractTransport>
#include <QtWebView>

class WebSocketTransport : public QWebChannelAbstractTransport {
  Q_OBJECT
public:
  using QWebChannelAbstractTransport::QWebChannelAbstractTransport;
  Q_INVOKABLE void sendMessage(const QJsonObject &message) override {
    QJsonDocument doc(message);
    emit messageChanged(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
  }
  Q_INVOKABLE void textMessageReceive(const QString &messageData) {
    QJsonParseError error;
    QJsonDocument message =
        QJsonDocument::fromJson(messageData.toUtf8(), &error);
    if (error.error) {
      qWarning() << "Failed to parse text message as JSON object:"
                 << messageData << "Error is:" << error.errorString();
      return;
    } else if (!message.isObject()) {
      qWarning() << "Received JSON message that is not an object: "
                 << messageData;
      return;
    }
    emit messageReceived(message.object(), this);
  }
signals:
  void messageChanged(const QString &message);
};

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  qmlRegisterType<WebSocketTransport>("com.eyllanesc.org", 1, 0,
                                      "WebSocketTransport");
  QtWebView::initialize();

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}

#include "main.moc"
