#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  ui->scrollArea->setWidgetResizable(true);

  QWidget *widget = new QWidget(this);
  ui->scrollArea->setWidget(widget);

  QGridLayout *gridLayout = new QGridLayout(widget);

  for (int i = 0; i < 20; i++) {
    QLabel *label = new QLabel(QString::number(i));
    gridLayout->addWidget(label, i, 1);

    QPushButton *button = new QPushButton(QString::number(i));
    gridLayout->addWidget(button, i, 10, 1, 1);
    button->setFixedSize(20, 20);
    button->setStyleSheet("background-color:red;");

    QRegion region(QRect(button->pos(), QSize(15, 15)), QRegion::Ellipse);
    button->setMask(region);
    button->hide();

    if (i == 5) {
      QLineEdit *lineEdit = new QLineEdit;
      gridLayout->addWidget(lineEdit, i, 5);

      connect(lineEdit, &QLineEdit::textChanged, [button](const QString &text) {
        button->setVisible(!text.isEmpty());
      });
    } else {
      QLineEdit *lineEdit_A = new QLineEdit;
      gridLayout->addWidget(lineEdit_A, i, 3);
      lineEdit_A->setValidator(new QIntValidator(0, 100, this));

      QLineEdit *lineEdit_B = new QLineEdit;
      gridLayout->addWidget(lineEdit_B, i, 7);
      lineEdit_B->setValidator(new QIntValidator(0, 100, this));

      connect(lineEdit_A, &QLineEdit::textChanged,
              [button](const QString &text) {
                button->setVisible(!text.isEmpty());
              });
      connect(lineEdit_B, &QLineEdit::textChanged,
              [button](const QString &text) {
                button->setVisible(!text.isEmpty());
              });
    }
  }

  gridLayout->setColumnMinimumWidth(1, 100);
  gridLayout->setColumnMinimumWidth(2, 10);
  gridLayout->setColumnMinimumWidth(4, 25);
  gridLayout->setColumnMinimumWidth(5, 50);
  gridLayout->setColumnMinimumWidth(6, 25);
  gridLayout->setColumnMinimumWidth(8, 10);
  gridLayout->setColumnMinimumWidth(9, 10);
  gridLayout->setColumnStretch(10, 20);
  gridLayout->setColumnMinimumWidth(10, 50);
  gridLayout->setColumnMinimumWidth(11, 10);
}

MainWindow::~MainWindow() { delete ui; }
