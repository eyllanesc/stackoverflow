#include "downloadmanager.h"
#include "downloaditem.h"

#include <QWebEngineDownloadItem>

DownloadManager::DownloadManager(QWidget *parent) : QWidget(parent) {
  setWindowTitle(tr("Downloads"));
  setLayout(new QVBoxLayout);
}

void DownloadManager::downloadItem(QWebEngineDownloadItem *download) {
  show();
  DownloadItem *downloadIt = new DownloadItem(download, this);
  layout()->addWidget(downloadIt);
  m_downloads.append(downloadIt);
  download->accept();
}
