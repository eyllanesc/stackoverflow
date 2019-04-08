#include "mainwindow.h"
#include "downloadmanager.h"
#include "webpage.h"

#include <QAction>
#include <QApplication>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QProgressBar>
#include <QStatusBar>
#include <QToolBar>
#include <QWebEngineHistory>

#include <functional>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_tabs(new QTabWidget),
      m_addTab(new QAction(tr("Add a Tab"))),
      m_deleteTab(new QAction(tr("Delete current Tab"))),
      m_quit(new QAction(tr("Quit"))),
      // Navigate
      m_previousPage(
          new QAction(QIcon(":/icones/prec.png"), tr("Previous Page"))),
      m_nextPage(new QAction(QIcon(":/icones/suiv.png"), tr("Next Page"))),
      m_reload(new QAction(QIcon(":/icones/actu.png"), tr("Reload"))),
      m_home(new QAction(QIcon(":/icones/home.png"), tr("Home Page"))),
      m_urlField(new QLineEdit),
      m_load(new QAction(QIcon(":/icones/go.png"), tr("Load the page"))),
      // About
      m_aboutMyChrome(new QAction(tr("About MyChrome"))),
      m_aboutQt(new QAction(tr("About Qt"))),
      m_downloadManager(new DownloadManager) {
  setCentralWidget(m_tabs);
  setWindowIcon(QIcon(":/icones/web.png"));

  m_addTab->setShortcut(QKeySequence(QKeySequence::AddTab));
  m_deleteTab->setShortcut(QKeySequence(QKeySequence::Close));
  m_previousPage->setShortcut(QKeySequence(QKeySequence::Back));
  m_nextPage->setShortcut(QKeySequence(QKeySequence::Forward));
  m_reload->setShortcut(QKeySequence(QKeySequence::Refresh));

  m_previousPage->setEnabled(false);
  m_nextPage->setEnabled(false);

  // Init menus and tool bars
  QMenu *fileMenu = menuBar()->addMenu(tr("File"));
  fileMenu->addAction(m_addTab);
  fileMenu->addAction(m_deleteTab);
  fileMenu->addAction(m_quit);

  QMenu *navigateMenu = menuBar()->addMenu(tr("Navigate"));
  navigateMenu->addAction(m_previousPage);
  navigateMenu->addAction(m_nextPage);
  navigateMenu->addAction(m_reload);
  navigateMenu->addAction(m_home);

  QMenu *aboutMenu = menuBar()->addMenu(tr("About"));
  aboutMenu->addAction(m_aboutMyChrome);
  aboutMenu->addAction(m_aboutQt);

  m_toolBar = addToolBar(tr("Navigate"));
  m_toolBar->addAction(m_previousPage);
  m_toolBar->addAction(m_nextPage);
  m_toolBar->addAction(m_reload);
  m_toolBar->addAction(m_home);
  m_toolBar->addWidget(m_urlField);
  m_toolBar->addAction(m_load);

  // Add status bar
  m_progress = new QProgressBar;
  statusBar()->addPermanentWidget(m_progress, 1);

  connect(m_addTab, &QAction::triggered, this, &MainWindow::addTab);
  connect(m_deleteTab, &QAction::triggered,
          std::bind(&MainWindow::removeTab, this, -1));

  connect(m_tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::removeTab);
  connect(m_quit, &QAction::triggered, qApp, &QApplication::quit);
  connect(m_reload, &QAction::triggered, this, &MainWindow::askReload);
  connect(m_home, &QAction::triggered, this, &MainWindow::askGoHome);
  connect(m_urlField, &QLineEdit::returnPressed,
          std::bind(&MainWindow::askLoad, this, ""));
  connect(m_load, &QAction::triggered,
          std::bind(&MainWindow::askLoad, this, ""));
  connect(m_aboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
  connect(m_tabs, &QTabWidget::currentChanged, this,
          &MainWindow::checkForwardBack);
  connect(m_previousPage, &QAction::triggered, this, &MainWindow::askGoBack);
  connect(m_nextPage, &QAction::triggered, this, &MainWindow::askGoForward);

  addTab();
}

MainWindow::~MainWindow() {}

void MainWindow::addTab() {
  WebPage *page = new WebPage(m_tabs);
  m_tabs->addTab(page, tr("Tab"));
  m_tabs->setCurrentWidget(page);
  page->load(QUrl(HOME_URL));
  connect(page, &WebPage::loadProgress, m_progress, &QProgressBar::setValue);
}

void MainWindow::removeTab(int index) {
  if (m_tabs->count() == 1)
    qApp->quit();
  if (index == -1)
    index = m_tabs->currentIndex();
  m_tabs->removeTab(index);
}

WebPage *MainWindow::currentPage() {
  return (WebPage *)m_tabs->currentWidget();
}

DownloadManager *MainWindow::downloadManager() { return m_downloadManager; }

void MainWindow::askLoad(const QString &url) {
  currentPage()->load(url.isEmpty() ? m_urlField->text() : url);
}

void MainWindow::askGoHome() { askLoad(HOME_URL); }

void MainWindow::askReload() { currentPage()->reload(); }

void MainWindow::checkForwardBack() {
  m_previousPage->setEnabled(currentPage()->history()->canGoBack());
  m_nextPage->setEnabled(currentPage()->history()->canGoForward());
}

void MainWindow::askGoBack() { currentPage()->history()->back(); }

void MainWindow::askGoForward() { currentPage()->history()->forward(); }

void MainWindow::hideToolBar() { m_toolBar->hide(); }

void MainWindow::showToolBar() { m_toolBar->show(); }

void MainWindow::changeUrlField(QString newText) {
  m_urlField->setText(newText);
}
