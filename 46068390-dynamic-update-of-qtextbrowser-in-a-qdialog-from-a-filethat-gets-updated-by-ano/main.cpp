#include "logdialog.h"
#include <QApplication>
#include <QProcess>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString filename = QDir::currentPath()+ "/data.log";

    QProcess process;
    process.setStandardOutputFile(filename);
#ifdef Q_OS_LINUX
    process.start("ping", QStringList()<< "8.8.8.8");
#elif Q_OS_WIN32
    process.start("ping", QStringList()<< "-t" <<"8.8.8.8");
#endif


    logdialog w(filename);
    w.show();

    return a.exec();
}
