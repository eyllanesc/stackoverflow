#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDebug>
#include <QNetworkReply>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://raw.githubusercontent.com/eyllanesc/stackoverflow/master/47361731/data.json"));
    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray data = reply->readAll();
    qDebug()<<data;

    return a.exec();
}
