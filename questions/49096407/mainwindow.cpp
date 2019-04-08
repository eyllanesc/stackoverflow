#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

  QMenuBar *menuBar = new QMenuBar(this);
  setMenuBar(menuBar);

  QMenu *fileMenu = new QMenu("&File", this);
  menuBar->addMenu(fileMenu);

  QAction *newTabAction = new QAction("&New Tab", this);
  fileMenu->addAction(newTabAction);
  connect(newTabAction, &QAction::triggered, this,
          &MainWindow::newTabActionHandler);

  tabWidget = new QTabWidget(this);
  tabWidget->setMovable(true);
  tabWidget->setTabsClosable(true);
  newTabActionHandler();

  setCentralWidget(tabWidget);
}

void MainWindow::newTabActionHandler() {
  QWidget *widget = new QWidget(this);
  widgetList << widget;
  tabWidget->addTab(widget, QString("Tab %1").arg(widgetList.size() - 1));

  QTextEdit *textEdit = new QTextEdit;
  textEditList << textEdit;
  QVBoxLayout *vBoxLayout = new QVBoxLayout(widget);
  vBoxLayout->addWidget(textEdit);
}

MainWindow::~MainWindow() {}
