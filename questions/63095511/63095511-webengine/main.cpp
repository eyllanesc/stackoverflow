#include <QtWebEngineWidgets>

#define SCHEMENAME "so"

class Handler : public QWebEngineUrlSchemeHandler{
public:
    void requestStarted(QWebEngineUrlRequestJob *job){
        if(job->requestUrl() == QUrl("so:/images/image.jpg")){
            QImage image(150, 150, QImage::Format_RGB32);
            image.fill(QColor("salmon"));

            QBuffer *buffer = new QBuffer;
            buffer->open(QIODevice::WriteOnly);
            image.save(buffer, "JPEG");
            buffer->seek(0);
            buffer->close();

            job->reply("image/jpeg", buffer);
        }
    }
    static void registerUrlScheme(){
        QWebEngineUrlScheme webUiScheme(SCHEMENAME);
        webUiScheme.setFlags(QWebEngineUrlScheme::SecureScheme |
                             QWebEngineUrlScheme::LocalScheme |
                             QWebEngineUrlScheme::LocalAccessAllowed);
        QWebEngineUrlScheme::registerScheme(webUiScheme);
    }

};


int main(int argc, char *argv[])
{
    Handler::registerUrlScheme();

    QApplication a(argc, argv);
    QWebEngineView view;

    Handler handler;
    view.page()->profile()->installUrlSchemeHandler(SCHEMENAME, &handler);
    view.resize(640, 480);
    view.show();

    QString html = R"(<img src="so:/images/image.jpg">)";
    view.setHtml(html);

    return a.exec();
}
