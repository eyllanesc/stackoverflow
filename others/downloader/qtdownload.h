#ifndef QTDOWNLOAD_H
#define QTDOWNLOAD_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class QtDownload : public QObject {
  Q_OBJECT
public:
  QtDownload(QObject *parent = 0);
  QNetworkAccessManager manager;
  QString target;

  void setTarget(const QString &t);

  QString getFilename() const;
  void setFilename(const QString &value);

private:
  QString filename;

signals:
  void done();
  void progress(qint64 recieved, qint64 total);

public slots:
  void download();
  void downloadFinished(QNetworkReply *data);
  void downloadProgress(qint64 recieved, qint64 total);
};

#endif // QTDOWNLOAD_H
