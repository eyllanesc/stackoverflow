#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(20);
    for(int i = 0; i<20;i++)
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QVector<QString>vec;
    vec<<"first"<<"sec"<<"third"<<"for"<<"fif"<<"first"<<"sec"
      <<"third"<<"for"<<"fif";
    vec<<"first"<<"sec"<<"third"<<"for"<<"fif"<<"first"<<"sec"
      <<"third"<<"for"<<"fif";

    for(int i = 0; i<ui->tableWidget->rowCount();i++)
    {
        for(int j = 0; j<ui->tableWidget->columnCount();j++)
        {
            if(j == 0){
                QWidget* pWidget = new QWidget(this);
                QPushButton* btn_edit = new QPushButton();
                btn_edit->setText("Remove");
                connect(btn_edit, &QPushButton::clicked, this, &MainWindow::onClicked);
                QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
                pLayout->addWidget(btn_edit);
                pLayout->setAlignment(Qt::AlignCenter);
                pLayout->setContentsMargins(0, 0, 0, 0);
                pWidget->setLayout(pLayout);
                ui->tableWidget->setCellWidget(i, j, pWidget);
                continue;

            }
            QTableWidgetItem*item = new QTableWidgetItem(vec[i]);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i, j, item);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClicked()
{
    QWidget *w = qobject_cast<QWidget *>(sender()->parent());
    if(w){
        int row = ui->tableWidget->indexAt(w->pos()).row();
        ui->tableWidget->removeRow(row);
        sender()->deleteLater();
        qDebug()<<sender();
        ui->tableWidget->setCurrentCell(0, 0);
    }
}
