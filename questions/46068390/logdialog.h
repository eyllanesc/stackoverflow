#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include <fstream>

namespace Ui {
class logdialog;
}

class logdialog : public QDialog
{
    Q_OBJECT

public:
    explicit logdialog(const QString &filename, QWidget *parent = 0);
    ~logdialog();
public:

    void fillloginfo();

    void initializeQTimer();

    void closeEvent(QCloseEvent *event);

    void fillLogInfoChronically(const QString& logFilePath);

private:

    QTimer* m_Timer;
    QString m_logFilePath;
    std::ifstream m_logFileStream;

public slots:

    void fillLogInfoChronicallySlot();

private:
    Ui::logdialog *uilog;
};

#endif // LOGDIALOG_H
