#include "webpage.h"
#include "downloadmanager.h"
#include "mainwindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QTabBar>
#include <QTabWidget>
#include <QWebEngineFullScreenRequest>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>

WebPage::WebPage(QTabWidget *parent) : QWebEngineView(parent), tabs(parent) {
  mainWindow = qobject_cast<MainWindow *>(parent->parentWidget());

  settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
  connect(this, &QWebEngineView::iconChanged, this, &WebPage::changeIcon);
  connect(this, &QWebEngineView::titleChanged, this, &WebPage::changeTitle);
  connect(this, &QWebEngineView::urlChanged, this, &WebPage::changeUrl);
  connect(page(), &QWebEnginePage::fullScreenRequested, this,
          &WebPage::setFullScreen);
  connect(page()->profile(), &QWebEngineProfile::downloadRequested,
          mainWindow->downloadManager(), &DownloadManager::downloadItem);
  connect(this, &QWebEngineView::loadProgress, mainWindow,
          &MainWindow::checkForwardBack);
}

void WebPage::changeTitle(const QString &title) {
  tabs->setTabText(tabs->indexOf(this), title);
}

void WebPage::changeIcon(QIcon icon) {
  tabs->setTabIcon(tabs->indexOf(this), icon);
}

void WebPage::changeUrl(QUrl url) {
  if (tabs->indexOf(this) == tabs->currentIndex())
    mainWindow->changeUrlField(url.toString());
}

void WebPage::setFullScreen(QWebEngineFullScreenRequest request) {

  if (request.toggleOn() && mainWindow->isFullScreen()) {
    qDebug("Already fullscreen");
    request.reject();
    return;
  }
  if (request.toggleOn()) {
    tabs->tabBar()->hide();

    mainWindow->menuBar()->hide();
    mainWindow->statusBar()->hide();
    mainWindow->hideToolBar();
    mainWindow->showFullScreen();

    request.accept();
  } else {
    tabs->tabBar()->show();

    mainWindow->menuBar()->show();
    mainWindow->statusBar()->show();
    mainWindow->showToolBar();
    mainWindow->showMaximized();

    request.accept();
  }
}
