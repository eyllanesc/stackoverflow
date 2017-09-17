#include "dialog.h"
#include "ui_dialog.h"

#include <QComboBox>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QTableView>
#include <QTimer>
#include <QLineEdit>
#include <QCompleter>

#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QTableView  *view = new QTableView(this);

    model = new QSqlTableModel;
    model->setTable("person");
    model->select();
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(1);

    ui->comboBox->setView(view);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->setMinimumWidth(500);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    model->setFilter(QString("country like '%1%'").arg(arg1));
    model->select();
}
