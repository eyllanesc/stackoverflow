#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QProgressBar;
class QLineEdit;
class WebPage;
class DownloadManager;

#define HOME_URL "http://www.lebbadi.fr"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  WebPage *currentPage();
  void askGoForward();
public slots:
  void addTab();
  void removeTab(int index);
  DownloadManager *downloadManager();
  void showToolBar();
  void hideToolBar();
  void askGoBack();
  void checkForwardBack();
  void askReload();
  void askGoHome();
  void askLoad(const QString &url = "");
  void changeUrlField(QString newText);

private:
  QTabWidget *m_tabs;
  QAction *m_addTab;
  QAction *m_deleteTab;
  QAction *m_quit;

  QToolBar *m_toolBar;

  QAction *m_previousPage;
  QAction *m_nextPage;
  QAction *m_reload;
  QAction *m_home;
  QLineEdit *m_urlField;
  QAction *m_load;

  QAction *m_aboutMyChrome;

  QProgressBar *m_progress;
  QAction *m_aboutQt;
  DownloadManager *m_downloadManager;
};

#endif // MAINWINDOW_H
