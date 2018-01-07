#include "widget.h"
#include "ui_widget.h"

#include <QDir>
#include <QIcon>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QStandardPaths>

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QDir dir (QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)[0]);
    const QFileInfoList &infolist = dir.entryInfoList(QDir::AllEntries | QDir::Dirs|QDir::NoDotAndDotDot);
    for(const QFileInfo &info: infolist){
        QIcon icon;
        icon.addFile(info.absoluteFilePath(), QSize(), QIcon::Normal, QIcon::Off);
        QPixmap pix = icon.pixmap(QSize(128,128));
        QWidget *w = new QWidget(ui->listWidget);
        w->setMinimumWidth(150);
        QVBoxLayout *lay = new QVBoxLayout(w);
        QLabel *lbl = new QLabel(w);
        lbl->setPixmap(pix);
        QComboBox *combo = new QComboBox(w);
        combo->addItem(info.baseName());

        lay->addWidget(lbl);
        lay->addWidget(combo);

        widget << w;
        layout << lay;
        box << combo;

        QListWidgetItem *qlistwidgetitem = new QListWidgetItem;
        qlistwidgetitem->setSizeHint(w->sizeHint());
        ui->listWidget->addItem(qlistwidgetitem);
        ui->listWidget->setItemWidget(qlistwidgetitem, w);
    }
}

Widget::~Widget()
{
    delete ui;
}
