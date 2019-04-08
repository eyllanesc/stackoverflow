#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"

#include <QMessageBox>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
}

Dialog::~Dialog() { delete ui; }

void Dialog::on_pushButton_clicked() {
  QString temp = ui->lineEdit->text(), temp_2 = ui->lineEdit_2->text(),
          temp_3 = ui->lineEdit_3->text();

  if (temp == "" || temp_2 == "" || temp_3 == "")
    QMessageBox ::warning(this, "Warning!", "One of the lines is empty");
  else {
    Book b(temp.toStdString(), temp_2.toStdString(), temp_3.toStdString());

    MainWindow *main_window = qobject_cast<MainWindow *>(parent());
    if (main_window)
      main_window->addBook(b);
    close();
  }
}
