#include "mainwindow.h"
#include "book.h"
#include "dialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentIndex(0) {
  ui->setupUi(this);

  Book b;
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
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionAdd_triggered() {

  d = new Dialog(this);
  d->show();
}

void MainWindow::on_next_clicked() {

  ++currentIndex;

  if (currentIndex < l.numOfBooks()) {
    Book b = l.getBook(currentIndex);

    ui->lineEdit->setText(QString::fromStdString(b.getName()));
    ui->lineEdit_2->setText(QString::fromStdString(b.getAuthor()));
    ui->lineEdit_3->setText(QString::fromStdString(b.getUid()));
  } else
    currentIndex = l.numOfBooks() - 1;
}

void MainWindow::on_previous_clicked() {

  --currentIndex;

  if (currentIndex >= 0) {
    Book b = l.getBook(currentIndex);

    ui->lineEdit->setText(QString::fromStdString(b.getName()));
    ui->lineEdit_2->setText(QString::fromStdString(b.getAuthor()));
    ui->lineEdit_3->setText(QString::fromStdString(b.getUid()));
  } else
    currentIndex = 0;
}

void MainWindow::addBook(const Book &b) { l.addBook(b); }
