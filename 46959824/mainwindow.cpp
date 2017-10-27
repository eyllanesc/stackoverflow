#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopServices>
#include <QFileInfo>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString hyperLink = QString::fromStdString("https://www.google.co.in/");
    hyperLink = QString::fromStdString("<a href = \"") + hyperLink +
            QString::fromStdString("\" >") + hyperLink + QString::fromStdString("</a>");
    hyperLink = QString::fromStdString("HyperLink: ") + hyperLink;
    ui->textBrowser->append(hyperLink);

    QString dirLocation = QString::fromStdString("/home/eyllanesc/Documents");
    dirLocation = QString::fromStdString("<a href = \"") + dirLocation +
            QString::fromStdString("\" >") + dirLocation + QString::fromStdString("</a>");
    dirLocation = QString::fromStdString("Working Directory: ") + dirLocation;
    ui->textBrowser->append(dirLocation);
    //connect(ui->textBrowser, &QTextBrowser::anchorClicked, this, &MainWindow::onAnchorClicked);
    connect(ui->textBrowser, SIGNAL(anchorClicked(QUrl)), this, SLOT(onAnchorClicked(QUrl)));
    ui->textBrowser->setOpenLinks(false);
    ui->textBrowser->setOpenExternalLinks(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAnchorClicked(const QUrl &link)
{
    if(!QFileInfo(link.toString()).isDir()){
        QDesktopServices::openUrl(link);
    }
    else{
        QProcess::startDetached(QString("gnome-terminal --working-directory=%1").arg(link.toString()));
    }
}
