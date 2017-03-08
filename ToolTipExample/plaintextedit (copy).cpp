#include "plaintextedit.h"
#include <QToolTip>


PlainTextEdit::PlainTextEdit(QWidget *parent):QPlainTextEdit(parent)
{
    setMouseTracking(true);
}

bool PlainTextEdit::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip)
    {
        QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
        QTextCursor cursor = cursorForPosition(helpEvent->pos());
        cursor.select(QTextCursor::WordUnderCursor);
        if (!cursor.selectedText().isEmpty())
            QToolTip::showText(helpEvent->globalPos(), cursor.selectedText());
        else
            QToolTip::hideText();
        return true;
    }
    return QPlainTextEdit::event(event);
}
