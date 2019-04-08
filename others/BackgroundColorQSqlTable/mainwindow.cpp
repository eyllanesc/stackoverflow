#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>

#include <QSqlError>

#include <QTableView>

#include "sqlrelationaltablemodel.h"

#include <QDir>
#include <QFileDialog>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  QString filename = QFileDialog::getOpenFileName(this, "Load Database",
                                                  QDir::homePath(), "*.db");
  if (!filename.isEmpty())
    loadDb(filename);
}

void MainWindow::loadDb(QString path) {
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path);
  if (!db.open()) {
    qWarning() << db.lastError().text();
    return;
  }

  modelUser = new SqlRelationalTableModel(this);
  modelUser->setTable("Users");
  modelCity = new QSqlTableModel(this);
  modelCity->setTable("City");
  modelUser->setRelation(2, QSqlRelation("City", "id", "name"));
  modelUser->select();

  ui->tableViewUsers->setModel(modelUser);
  delegate = new QSqlRelationalDelegate(this);
  ui->tableViewUsers->setItemDelegate(delegate);

  ui->tableViewCity->setModel(modelCity);
  modelCity->select();
}
