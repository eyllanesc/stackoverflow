#include <QCoreApplication>
#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStandardPaths>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QNetworkAccessManager nam;

  QNetworkRequest request(
      QUrl("http://rfm-live-mp3-64.scdn.arkena.com/rfm.mp3"));

  QString downloadDir =
      QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

  QFile file(QDir(downloadDir).absoluteFilePath("test.mp3"));

  QDataStream ds(&file);

  if (!file.open(QFile::WriteOnly))
    return -1;

  QNetworkReply *reply = nam.get(request);
  QObject::connect(reply, &QNetworkReply::downloadProgress,
                   [reply, &ds](qint64 bytesReceived, qint64 bytesTotal) {
                     ds << reply->readAll();
                     qDebug() << bytesReceived << bytesTotal;
                   });

  qDebug() << reply;

  return a.exec();
}
