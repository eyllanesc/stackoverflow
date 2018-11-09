#ifndef GLINEEDITDIALOG_H
#define GLINEEDITDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <glineedit.h>

class GLineEditDialog : public QDialog
{
    Q_OBJECT
public:
    GLineEditDialog(GLineEdit *plugin = 0, QWidget *parent = 0);

    QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    GLineEdit *editor;
    GLineEdit *linedit;
    QDialogButtonBox *buttonBox;
};

#endif // GLINEEDITDIALOG_H
