#ifndef FOCUSLINEEDIT_H
#define FOCUSLINEEDIT_H

#include <QObject>
#include <QLineEdit>

class FocusLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    FocusLineEdit(QWidget *parent);

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private slots:
    void on_textChanged(const QString &str);

signals:
    void focusChanged(bool);
    void cleared(bool);
};

#endif // FOCUSLINEEDIT_H
