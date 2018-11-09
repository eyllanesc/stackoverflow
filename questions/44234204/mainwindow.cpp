#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebEngineView *view;
    QString pdfFileURL;

    QString pathToPDFjs = QString("file:///%1/%2")
            .arg(QDir::currentPath())
            .arg("3rdParty/pdfjs-1.7.225-dist/web/viewer.html");

    pdfFileURL = QString("file:///%1/%2").arg(QDir::currentPath()).arg("CV.pdf");

    view = new QWebEngineView();
    setCentralWidget(view);

    QUrl url = QUrl::fromUserInput(pathToPDFjs + QString("?file=") + pdfFileURL);

    view->load(url);
}

MainWindow::~MainWindow()
{
    delete ui;
}
