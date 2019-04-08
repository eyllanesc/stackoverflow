#ifndef HTTPCONTROLLER_H
#define HTTPCONTROLLER_H

#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QObject>

class HttpController : public QObject {
  Q_OBJECT
public:
  explicit HttpController(QObject *parent = 0);
  QString Get(const QString &url);
  QString Post(const QString &url, QHttpMultiPart *multipart);
signals:

public slots:
private:
  QNetworkCookieJar *cookies;
  QNetworkAccessManager *manager;
};

#endif // HTTPCONTROLLER_H
