#ifndef MYSERVER_H
#define MYSERVER_H

#include "mainwindow.h"

#include <QTcpServer>

class MyServer : public QTcpServer {
public:
  using QTcpServer::QTcpServer;
  void startServer();

private:
  MainWindow *instance = MainWindow::instance();
  void sockReady();
  void sockDisc();
};

#endif // MYSERVER_H
