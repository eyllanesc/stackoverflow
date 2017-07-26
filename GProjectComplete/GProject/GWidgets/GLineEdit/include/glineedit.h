#ifndef GLINEEDIT_H
#define GLINEEDIT_H

#include "glineedit_global.h"
#include <QWidget>
#include <QVBoxLayout>

#include "focuslabel.h"
#include "focuslineedit.h"


class GLINEEDITSHARED_EXPORT GLineEdit : public QWidget
{

public:
    GLineEdit(QWidget *parent = 0);

    QString text() const;
    void setText(const QString &str);
    void setTitle(const QString &str);

private:
    FocusLabel *m_label;
    FocusLineEdit *m_lineEdit;
};

#endif // GLINEEDIT_H
