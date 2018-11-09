#include "sslserver.h"

#include <QCoreApplication>

#include <QLoggingCategory>

int main(int argc, char *argv[]){

    QCoreApplication a(argc, argv);
    QLoggingCategory::setFilterRules("*.debug=true");

    SslServer *myTestServer = new SslServer();

    return a.exec();
}
