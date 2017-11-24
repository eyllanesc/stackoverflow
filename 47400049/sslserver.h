#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class SslServer : public QObject
{
    Q_OBJECT
public:
    explicit SslServer(QObject *parent = nullptr);

private slots:
    void newTestConnection();
    void sendTestdata();
    void connectionWasClosed(QAbstractSocket::SocketState state);

private:
    QTcpServer *testServer;
    QTcpSocket *testSocket;
    QTimer *testTimer;
};

#endif // SSLSERVER_H
