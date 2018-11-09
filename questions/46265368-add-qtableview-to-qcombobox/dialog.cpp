#include "dialog.h"
#include "ui_dialog.h"

#include <QComboBox>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QTableView>
#include <QTimer>
#include <QLineEdit>
#include <QCompleter>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>

#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QTableView  *view = new QTableView(this);

    model = new QSqlTableModel;
    model->setTable("TableTest");
    model->select();

    const QString tableName("TableTest");

    QSqlQuery q(QString("SELECT DISTINCT continentName FROM %1").arg(tableName));
    q.exec();
    while (q.next()) {
        ui->ContinentComboBox->addItem(q.value(0).toString());
    }


    ui->CountryComboBox->setModel(model);
    ui->CountryComboBox->setModelColumn(2);
    ui->CountryComboBox->setView(view);
    view->hideColumn(0);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->setMinimumWidth(900);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_ContinentComboBox_currentTextChanged(const QString &name)
{
    model->setFilter(QString("continentName= '%1' ").arg(name));
    model->select();
}
