#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFrame>
#include <QSignalMapper>

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
    void on_pushButton_clicked();
    void Run();
    void Stop();
    void onClicked(const QString &text);

private:
    void createButtons();
    Ui::Dialog *ui;
    QStringList List;
    QSignalMapper *signalMapper;
};

#endif // DIALOG_H
