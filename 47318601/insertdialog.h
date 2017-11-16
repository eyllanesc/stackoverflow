#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

class InsertDialog : public QDialog
{
    Q_OBJECT
public:
    InsertDialog(QWidget *parent = 0):QDialog(parent){
        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel, Qt::Horizontal, this);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

        mF = new QLineEdit(this);
        mL = new QLineEdit(this);
        QVBoxLayout *lay = new QVBoxLayout(this);
        QFormLayout *flay = new QFormLayout;
        flay->addRow("Firstname:", mF);
        flay->addRow("Lastname:", mL);

        lay->addLayout(flay);
        lay->addWidget(buttonBox);

        connect(mF, &QLineEdit::textChanged, this, &InsertDialog::setFirstname);
        connect(mL, &QLineEdit::textChanged, this, &InsertDialog::setLastname);
    }
    ~InsertDialog(){
    }
    QString firstname() const{
        return mFirstname;
    }

    QString lastname() const{
        return mLastname;
    }

    void setFirstname(const QString &firstname){
        mFirstname = firstname;
    }

    void setLastname(const QString &lastname){
        mLastname = lastname;
    }

private:
    QDialogButtonBox *buttonBox;
    QString mFirstname;
    QString mLastname;
    QLineEdit *mF;
    QLineEdit *mL;
};

#endif // INSERTDIALOG_H
