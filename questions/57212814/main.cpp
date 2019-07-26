#include <QtWidgets>
#include <QtNetwork>

class SuggestModel: public QStandardItemModel
{
    Q_OBJECT
public:
    using QStandardItemModel::QStandardItemModel;
    void search(const QString & text)
    {
        QNetworkRequest request = create_request(text);
        if(m_reply)
            m_reply->abort();
        m_reply = manager.get(request);
        connect(m_reply, &QNetworkReply::finished, this, &SuggestModel::onFinished);
        QEventLoop loop;
        connect(this, &SuggestModel::finished, &loop, &QEventLoop::quit);
        loop.exec();
    }
private Q_SLOTS:
    void onFinished(){
        QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
        QUrl url = reply->url();
        if (reply->error() == QNetworkReply::NoError) {
            QVector<QString> choices;
            QByteArray response(reply->readAll());
            QXmlStreamReader xml(response);
            while (!xml.atEnd()) {
                xml.readNext();
                if (xml.tokenType() == QXmlStreamReader::StartElement)
                    if (xml.name() == "suggestion") {
                        QStringRef str = xml.attributes().value("data");
                        choices << str.toString();
                    }
            }
            clear();
            for(const QString & choice: choices)
                appendRow(new QStandardItem(choice));

        }
        reply->deleteLater();
        Q_EMIT finished();
        m_reply = nullptr;
    }
Q_SIGNALS:
    void finished();
private:
    QNetworkRequest create_request(const QString & text){
        const QString suggestUrl(QStringLiteral("http://google.com/complete/search?output=toolbar&q=%1"));
        QString url = suggestUrl.arg(text);
        return QNetworkRequest(url);
    }
    QNetworkAccessManager manager;
    QNetworkReply *m_reply = nullptr;
};

class SuggestCompleter: public QCompleter{
public:
    SuggestCompleter(QObject *parent=nullptr):
        QCompleter(parent)
    {
        SuggestModel *m_model = new SuggestModel(this);
        setModel(m_model);
        setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    }
    QStringList splitPath(const QString &path) const override{
        if(SuggestModel * m = qobject_cast<SuggestModel *>(model()))
            m->search(path);
        return QCompleter::splitPath(path);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLineEdit le;
    le.setCompleter(new SuggestCompleter(&le));
    le.show();
    return a.exec();
}

#include "main.moc"
