#include <QCoreApplication>
#include <QFile>
#include <QDebug>

#include <qconsole.h>

#include "score.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Score score;

    QConsole console;
    QObject::connect(&console, &QConsole::readyRead, [&](){
        auto data = console.read(console.bytesAvailable());
        if(data == QStringLiteral("1\n")){
            score.stop();
        }
        else if(data == QStringLiteral("2\n")){
            score.start();
        }
    });
    if(!console.open()) {
        qCritical() << console.errorString();
        return EXIT_FAILURE;
    }
    return a.exec();
}
