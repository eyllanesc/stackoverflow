#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

#include "nativemessenger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NativeMessenger listener;
    QObject::connect(&listener, &NativeMessenger::messageChanged,
                     [&listener]
                     (const QByteArray & message){
        QJsonParseError error;
        QJsonDocument json = QJsonDocument::fromJson(message, &error);
        if(error.error != QJsonParseError::NoError){
            qDebug() << error.errorString();
        }
        QJsonObject object
        {
            {"data", json.object()},
            {"name", QCoreApplication::applicationName()}
        };
        QByteArray response = QJsonDocument(object).toJson(QJsonDocument::Compact);
        listener.sendMessage(response);
    });
    return a.exec();
}
