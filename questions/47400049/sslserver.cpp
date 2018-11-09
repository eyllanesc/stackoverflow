#include "sslserver.h"
#include <QDebug>

SslServer::SslServer(QObject *parent) : QObject(parent){

    testServer = new QTcpServer(this);
    testTimer = new QTimer();

    connect(testServer, &QTcpServer::newConnection, this, &SslServer::newTestConnection);  //works
    connect(testTimer, &QTimer::timeout, this, &SslServer::sendTestdata);              //works

    testTimer->start(1000);

    if(testServer->listen(QHostAddress::Any, 9999)){
        qDebug() << "Server running on Port 9999";
    }else{
        qDebug() << "Error while building server";
    }

}

void SslServer::newTestConnection(){
    if(testSocket)
        testSocket->close();
    testSocket = testServer->nextPendingConnection();
    connect(testSocket, &QAbstractSocket::stateChanged, this, &SslServer::connectionWasClosed);
    testSocket->write("Welcome on: Testserver!");
    testSocket->flush();
}

void SslServer::sendTestdata(){
    if(testSocket){
        if(testSocket->isOpen()){
            qDebug() << testSocket->state();
            qDebug() << "Sending testdata to client";
            testSocket->write("testdata");
        }
    }
}

void SslServer::connectionWasClosed(QAbstractSocket::SocketState state){

    qDebug() << "!!! SocketState changed !!!" << state;
}
