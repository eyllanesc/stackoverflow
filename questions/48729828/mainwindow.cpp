#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QDir>
#include <QDirIterator>
#include <QFileInfoList>
#include <QListWidget>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QDir dir(":/icons");
  QFileInfoList fileInfoList =
      dir.entryInfoList(QDir::AllEntries | QDir::Dirs | QDir::NoDotAndDotDot);

  for (const QFileInfo &finfo : fileInfoList) {
    QIcon icon;
    icon.addFile(finfo.absoluteFilePath(), QSize(), QIcon::Normal, QIcon::Off);
    QListWidgetItem *item = new QListWidgetItem;
    item->setIcon(icon);
    ui->listwidget1->insertItem(ui->listwidget1->count(), item);
    QComboBox *box = new QComboBox;
    box->addItems(QStringList{finfo.baseName(), "item1", "item2", "item3"});
    ui->listwidget1->setItemWidget(item, box);
    QSize size = item->sizeHint();
    size.setHeight(box->sizeHint().height());
    item->setSizeHint(size);
  }
}

MainWindow::~MainWindow() { delete ui; }
