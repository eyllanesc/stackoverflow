#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_ContinentComboBox_currentTextChanged(const QString &name);

private:
    Ui::Dialog *ui;
    QSqlTableModel *model;
};

#endif // DIALOG_H
