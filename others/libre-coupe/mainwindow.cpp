#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  book b;
  b.setAuthor("Ruskin Bond");
  b.setName("The Jungle Book");
  b.setUid("123456789");

  l.addBook(b);

  b.setAuthor("Savi Sharma");
  b.setName("This is not your story");
  b.setUid("789456123");

  l.addBook(b);

  b = l.getBook(0);
  ui->lineEdit->setText(QString::fromStdString(b.getName()));
  ui->lineEdit_2->setText(QString::fromStdString(b.getAuthor()));
  ui->lineEdit_3->setText(QString::fromStdString(b.getUid()));

  currentIndex = 0;
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_next_clicked() {
  ++currentIndex;

  if (currentIndex < l.numOfBooks()) {
    book b;

    b = l.getBook(currentIndex);

    ui->lineEdit->setText(QString::fromStdString(b.getName()));
    ui->lineEdit_2->setText(QString::fromStdString(b.getAuthor()));
    ui->lineEdit_3->setText(QString::fromStdString(b.getUid()));
  }
}

void MainWindow::on_previous_clicked() {
  --currentIndex;

  if (currentIndex >= 0) {
    book b;

    b = l.getBook(currentIndex);

    ui->lineEdit->setText(QString::fromStdString(b.getName()));
    ui->lineEdit_2->setText(QString::fromStdString(b.getAuthor()));
    ui->lineEdit_3->setText(QString::fromStdString(b.getUid()));
  }
}

void MainWindow::on_actionAdd_book_triggered() {
  Dialog d(this);
  d.exec();
}

void MainWindow ::addBook(const book &b) { l.addBook(b); }
