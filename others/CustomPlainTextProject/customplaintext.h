#ifndef CUSTOMPLAINTEXT_H
#define CUSTOMPLAINTEXT_H

#include <QPlainTextEdit>

class CustomPlainText : public QPlainTextEdit {
  Q_OBJECT
public:
  CustomPlainText(QWidget *parent = 0);
  void CustomSetViewportMargins(int left, int top, int right, int bottom);
  void CustomSetViewportMargins(const QMargins &margins);
};

#endif // CUSTOMPLAINTEXT_H
