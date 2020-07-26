#include <QtWebKitWidgets>

class CustomReply : public QNetworkReply{
public:
    explicit CustomReply(const QByteArray & content, const QByteArray & contentType, const QUrl & url):
        QNetworkReply(), m_content(content){
        offset = 0;
        setUrl(url);
        open(ReadOnly | Unbuffered);
        setHeader(QNetworkRequest::ContentTypeHeader, QVariant(contentType));
        setHeader(QNetworkRequest::ContentLengthHeader, QVariant(m_content.size()));
        QTimer::singleShot(0, this, &CustomReply::dispatch);
    }
    bool isSequential() const{
        return true;
    }
    qint64 bytesAvailable() const{
        return m_content.size() - offset + QIODevice::bytesAvailable();
    }
public slots:
    void abort(){
    }
protected:
    qint64 readData(char *data, qint64 maxSize){
        if (offset < m_content.size()) {
            qint64 number = qMin(maxSize, m_content.size() - offset);
            ::memcpy(data, m_content.constData() + offset, number);
            offset += number;
            return number;
        } else
            return -1;
    }
private:
    void dispatch(){
        emit readyRead();
        emit finished();
    }
    QByteArray m_content;
    qint64 offset;
};

class NetworkAccessManager: public QNetworkAccessManager{
public:
    using QNetworkAccessManager::QNetworkAccessManager;
protected:
    QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData){
        qDebug() << request.url();
        if (request.url() == QUrl("qrc:/images/image.jpg")){

            QImage image(150, 150, QImage::Format_RGB32);
            image.fill(QColor("salmon"));

            QByteArray ba;
            QBuffer buffer(&ba);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "JPEG");

            return new CustomReply(ba, "image/jpeg", request.url());
        }
        return QNetworkAccessManager::createRequest(op, request, outgoingData);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWebView view;
    view.resize(640, 480);
    view.show();

    view.page()->setNetworkAccessManager(new NetworkAccessManager);

    QString html = R"(<img src="qrc:/images/image.jpg">)";
    view.setHtml(html);
    return a.exec();
}
