#include "customplaintext.h"

CustomPlainText::CustomPlainText(QWidget *parent) : QPlainTextEdit(parent) {}

void CustomPlainText::CustomSetViewportMargins(int left, int top, int right,
                                               int bottom) {
  setViewportMargins(left, top, right, bottom);
}

void CustomPlainText::CustomSetViewportMargins(const QMargins &margins) {
  setViewportMargins(margins);
}
