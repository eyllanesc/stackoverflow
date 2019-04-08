#include "qtdownload.h"
#include <QDebug>
#include <QFile>

QtDownload::QtDownload(QObject *parent) : QObject(parent) {
  QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), this,
                   SLOT(downloadFinished(QNetworkReply *)));
}

void QtDownload::setTarget(const QString &t) { this->target = t; }

QString QtDownload::getFilename() const { return filename; }

void QtDownload::setFilename(const QString &value) { filename = value; }

void QtDownload::downloadFinished(QNetworkReply *data) {
  QFile localFile(filename);
  if (!localFile.open(QIODevice::WriteOnly))
    return;
  const QByteArray sdata = data->readAll();
  localFile.write(sdata);
  localFile.close();
  emit done();
}

void QtDownload::download() {
  QUrl url = QUrl::fromEncoded(this->target.toLocal8Bit()).scheme();
  QNetworkRequest request(url);
  QNetworkReply *reply = manager.get(request);
  QObject::connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this,
                   SLOT(downloadProgress(qint64, qint64)));
}

void QtDownload::downloadProgress(qint64 recieved, qint64 total) {
  qDebug() << recieved << total;
  emit(progress(recieved, total));
}
