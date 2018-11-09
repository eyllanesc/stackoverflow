#include "dialog.h"
#include "ui_dialog.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    signalMapper = new QSignalMapper(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    createButtons();
}

void Dialog::createButtons()
{
    List<<"Run"<<"Stop";
    for(const QString &text : List ){
        QPushButton* a= new QPushButton(this);
        a->setText(text);
        ui->horizontalLayout->addWidget(a);
        connect(a, &QAbstractButton::clicked, signalMapper, QOverload<>::of(&QSignalMapper::map));
        signalMapper->setMapping(a, text);
    }
    connect(signalMapper, QOverload<const QString &>::of(&QSignalMapper::mapped), this, &Dialog::onClicked);
}

void Dialog::onClicked(const QString &text)
{
    QMetaObject::invokeMethod(this, text.toLatin1().data());
}


void Dialog::Run(){
    qDebug() << "You clicked on the Run button";

}
void Dialog::Stop(){
    qDebug() << "You clicked on the Stop button";
}

