#include "dialog.h"
#include "ui_dialog.h"

#include <QTableView>
#include <QSqlError>
#include <QDir>
#include <QFileDialog>

#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Custom QSqlTableModel");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::currentPath(),
                                                    tr("SQLite Database files(*.db *.db3 *.sqlite *.sqlite3)"));
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if(!db.open()){
        qWarning()<<db.lastError().text();
        return;
    }

    model = new SqlTableModel;
    model->setTable("TableExample");
    ui->tableView->setModel(model);
    model->select();
}
