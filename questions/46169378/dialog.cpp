#include "dialog.h"
#include "ui_dialog.h"

#include <QDir>
#include <QFileDialog>
#include <QSqlError>
#include <QTableView>

#include <QDebug>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
  setWindowTitle("Custom QSqlTableModel");

  model = new SqlTableModel;
  model->setTable("TableExample");
  ui->tableView->setModel(model);
  model->select();
}

Dialog::~Dialog() { delete ui; }
