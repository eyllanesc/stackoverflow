#include "myserver.h"

#include <QDebug>
#include <QTcpSocket>

void MyServer::startServer() {
  if (listen(QHostAddress::Any, 5555))
    qDebug() << "LISTEN";
  else
    qDebug() << "NOT LISTEN";
  connect(this, &QTcpServer::newConnection, this, &MyServer::sockReady);
}

void MyServer::sockReady() {
  QTcpSocket *socket = nextPendingConnection();
  qDebug() << "CONNECTED";
  instance->drawConnection();
  connect(socket, &QTcpSocket::disconnected, this, &MyServer::sockDisc);
}

void MyServer::sockDisc() {
  QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
  qDebug() << "DISCONECT";
  if (socket)
    socket->deleteLater();
}
