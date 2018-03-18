#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCompleter>
#include <QLineEdit>
#include <QTableWidget>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(5);

    QStringList wordList{"alpha", "omega", "omega2", "omega3", "omicron", "zeta"};

    for(int i = 0; i<5;i++){

        QLineEdit *lineEdit = new QLineEdit;
        QCompleter *completer = new QCompleter(wordList);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        connect(lineEdit, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);
        lineEdit->setCompleter(completer);
        lineEdit->setProperty("row", i);
        lineEdit->setProperty("column", i);
        ui->tableWidget->setCellWidget(i,i,lineEdit);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTextChanged(const QString &text)
{
    QLineEdit *le = static_cast<QLineEdit *>(sender());
    qDebug()<< le->property("row").toInt()<<le->property("column").toInt()<<text;

}
