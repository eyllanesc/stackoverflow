#include "plaintextedit.h"
#include <QToolTip>

PlainTextEdit::PlainTextEdit(QWidget *parent) : QPlainTextEdit(parent) {
  setMouseTracking(true);
}

bool PlainTextEdit::event(QEvent *event) {
  if (event->type() == QEvent::ToolTip) {
    QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
    QTextCursor cursor = cursorForPosition(helpEvent->pos());
    cursor.select(QTextCursor::WordUnderCursor);
    if (!cursor.selectedText().isEmpty())
      QToolTip::showText(helpEvent->globalPos(),
                         /*your text*/ QString("%1 %2")
                             .arg(cursor.selectedText())
                             .arg(cursor.selectedText().length()));
    else
      QToolTip::hideText();
    return true;
  }
  return QPlainTextEdit::event(event);
}
