#ifndef DOWNLOADITEM_H
#define DOWNLOADITEM_H

#include <QWebEngineDownloadItem>
#include <QWidget>
class QProgressBar;
class QLabel;
class QAction;
class QLabel;

class DownloadItem : public QWidget {
  Q_OBJECT
public:
  explicit DownloadItem(QWebEngineDownloadItem *origin,
                        QWidget *parent = nullptr);

public slots:
  void displayProgress(qint64 current, qint64 total);
  void showContextMenu(QPoint pos);
  void open();
  void openInFiles();
  void pauseRequest();
  void displayState(QWebEngineDownloadItem::DownloadState state);

private:
  QWebEngineDownloadItem *m_download;
  QProgressBar *m_progress;
  QAction *m_pause;
  QLabel *m_state;
};

#endif // DOWNLOADITEM_H
