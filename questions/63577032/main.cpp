#include <QtCore>
#include <QtNetwork>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QNetworkAccessManager qnam;

    QObject::connect(&qnam, &QNetworkAccessManager::finished, [](QNetworkReply *reply){
        if(reply->error() == QNetworkReply::NoError){
            qDebug() << QString(reply->readAll());
        }
        else
            qDebug() << reply->error() << reply->errorString();
        reply->deleteLater();
        QCoreApplication::quit();
    });

    QUrl url("http://ssltsw.forexprostools.com/index.php?timeframe=300&lang=1&forex=1&commodities=8830,8836,8831,8849,8833,8862,8832&indices=175,166,172,27,179,170,174&stocks=334,345,346,347,348,349,350&tabs=1,2,3,4%22%20width=%22317%22%20height=%22467%22%3E%3C/iframe%3E%3Cdiv%20class=%22poweredBy%22%20style=%22font-family:arial,helvetica,sans-serif;%20direction:ltr;%22%3E%3Cspan%20style=%22font-size:%2011px;color:%20&selectedTabId=QBS_1");
    QNetworkRequest request;
    request.setUrl(url);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    qnam.get(request);

    return a.exec();
}
