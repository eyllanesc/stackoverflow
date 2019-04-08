#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QPlainTextEdit>

class PlainTextEdit : public QPlainTextEdit {
public:
  PlainTextEdit(QWidget *parent = 0);

  bool event(QEvent *event);
};

#endif // PLAINTEXTEDIT_H
