#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QVBoxLayout>
#include <QWidget>
class DownloadItem;
class QWebEngineDownloadItem;

class DownloadManager : public QWidget {
  Q_OBJECT
public:
  explicit DownloadManager(QWidget *parent = nullptr);

public slots:
  void downloadItem(QWebEngineDownloadItem *download);

private:
  QList<DownloadItem *> m_downloads;
};

#endif // DOWNLOADMANAGER_H
