#include "httpcontroller.h"

#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>

HttpController::HttpController(QObject *parent) : QObject(parent) {
  cookies = new QNetworkCookieJar;
  manager = new QNetworkAccessManager(parent);

  manager->setCookieJar(cookies);
}

QString HttpController::Get(const QString &url) {
  QNetworkRequest request;
  request.setUrl(QUrl(url));

  QNetworkReply *reply = manager->get(request);

  QEventLoop loop;

  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop,
          SLOT(quit()));
  loop.exec();

  if (reply->error())
    return QString("Error");
  QString response = QString(reply->readAll());
  reply->deleteLater();
  return response;
}

QString HttpController::Post(const QString &url, QHttpMultiPart *multipart) {
  QNetworkRequest request;
  request.setUrl(QUrl(url));

  QNetworkReply *reply = manager->post(request, multipart);

  QEventLoop loop;
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop,
          SLOT(quit()));
  loop.exec();

  if (reply->error())
    return QString("Error");
  QString response = QString(reply->readAll());
  reply->deleteLater();
  return response;
}
