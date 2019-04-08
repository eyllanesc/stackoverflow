#include "widget.h"
#include "ui_widget.h"

#include <QComboBox>
#include <QDir>
#include <QIcon>
#include <QLabel>
#include <QListWidgetItem>
#include <QStandardPaths>
#include <QVBoxLayout>

#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  QDir dir(
      QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)[0]);
  const QFileInfoList &infolist =
      dir.entryInfoList(QDir::AllEntries | QDir::Dirs | QDir::NoDotAndDotDot);
  for (const QFileInfo &info : infolist) {
    QIcon icon;
    icon.addFile(info.absoluteFilePath(), QSize(), QIcon::Normal, QIcon::Off);
    QPixmap pix = icon.pixmap(QSize(128, 128));
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
    pic << lbl;

    QListWidgetItem *qlistwidgetitem = new QListWidgetItem;
    qlistwidgetitem->setSizeHint(w->sizeHint());
    qlistwidgetitem->setData(Qt::UserRole, QVariant::fromValue(icon));
    ui->listWidget->addItem(qlistwidgetitem);
    ui->listWidget->setItemWidget(qlistwidgetitem, w);
  }
  ui->horizontalSlider->setMaximum(200);
  on_horizontalSlider_valueChanged(ui->horizontalSlider->value());
}

Widget::~Widget() { delete ui; }

void Widget::on_horizontalSlider_valueChanged(int value) {
  for (int i = 0; i < ui->listWidget->count(); i++) {
    QListWidgetItem *it = ui->listWidget->item(i);
    QIcon icon = it->data(Qt::UserRole).value<QIcon>();
    pic[i]->setPixmap(icon.pixmap(value, value));
    QWidget *w = ui->listWidget->itemWidget(it);
    it->setSizeHint(w->sizeHint());
  }
}
