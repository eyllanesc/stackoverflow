#include "passwordlineedit.h"

#include <QApplication>
#include <QFormLayout>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QWidget w;
  PasswordLineEdit *w1 = new PasswordLineEdit;
  QLineEdit *w2 = new QLineEdit;
  QFormLayout *lay = new QFormLayout(&w);
  lay->addRow("PasswordLineEdit: ", w1);
  lay->addRow("QLineEdit: ", w2);
  w.show();

  return a.exec();
}
