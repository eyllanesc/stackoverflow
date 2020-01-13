#include "spotifywrapper.h"

#include <QNetworkReply>
#include <QGuiApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    SpotifyWrapper wrapper;
    wrapper.grant();
    QObject::connect(&wrapper, &SpotifyWrapper::authenticated, [&wrapper](){
        qDebug() << "authenticated";
        QNetworkReply *reply = wrapper.me();
        QObject::connect(reply, &QNetworkReply::finished, [=]() {
                reply->deleteLater();
                if (reply->error() != QNetworkReply::NoError) {
                    qDebug() << reply->errorString();
                    return;
                }
                qDebug() << reply->readAll();
                QTimer::singleShot(1000, &QCoreApplication::quit);
        });
    });
    return a.exec();
}
