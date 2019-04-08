#ifndef DIALOG_H
#define DIALOG_H

#include "book.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();

signals:
  void bookDetailsEntered(book b);

private slots:
  void on_okay_clicked();

private:
  Ui::Dialog *ui;
};

#endif // DIALOG_H
