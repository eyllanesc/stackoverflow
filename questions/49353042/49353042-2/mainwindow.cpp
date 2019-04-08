#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCompleter>
#include <QLineEdit>
#include <QTableWidget>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tableWidget->setRowCount(5);
  ui->tableWidget->setColumnCount(5);

  QStringList wordList{"alpha", "omega", "omega2", "omega3", "omicron", "zeta"};

  for (int i = 0; i < 5; i++) {

    QLineEdit *lineEdit = new QLineEdit;
    QCompleter *completer = new QCompleter(wordList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    connect(completer, qOverload<const QString &>(&QCompleter::activated), this,
            &MainWindow::onActivated);
    lineEdit->setCompleter(completer);
    completer->setProperty("row", i);
    completer->setProperty("column", i);
    ui->tableWidget->setCellWidget(i, i, lineEdit);
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onActivated(const QString &text) {
  QCompleter *completer = static_cast<QCompleter *>(sender());
  qDebug() << completer->property("row").toInt()
           << completer->property("column").toInt() << text;
}
