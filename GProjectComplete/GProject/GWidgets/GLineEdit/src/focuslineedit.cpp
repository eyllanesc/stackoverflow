#include "focuslineedit.h"

FocusLineEdit::FocusLineEdit(QWidget *parent) : QLineEdit(parent)
{
    connect(this, &FocusLineEdit::textChanged, this, &FocusLineEdit::on_textChanged);
}

void FocusLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);

    focusChanged(true);
}

void FocusLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);

    focusChanged(false);
}

void FocusLineEdit::on_textChanged(const QString &str)
{
    cleared(str.isEmpty());
}
