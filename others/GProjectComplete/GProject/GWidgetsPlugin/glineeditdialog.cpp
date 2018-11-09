#include "glineeditdialog.h"

GLineEditDialog::GLineEditDialog(GLineEdit *plugin, QWidget *parent):
    QDialog(parent),
    editor(new GLineEdit),
    linedit(plugin),
    buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok
                                   | QDialogButtonBox::Cancel
                                   | QDialogButtonBox::Reset))
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(editor);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle(tr("Edit Actions"));
}


QSize GLineEditDialog::sizeHint() const
{
    return QSize(250, 250);
}
