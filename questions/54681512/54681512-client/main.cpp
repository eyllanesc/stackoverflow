#include "objects.h"

#include <QCoreApplication>
#include <rep_remoteminimal_replica.h>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QSharedPointer<RemoteMinimalReplica> ptr;

  QRemoteObjectNode repNode;
  repNode.connectToNode(QUrl(QStringLiteral("local:remote_minimal")));
  ptr.reset(repNode.acquire<RemoteMinimalReplica>());

  Objects *cl1 = new Objects(ptr);
  Objects *cl2 = new Objects(ptr);
  Objects *cl3 = new Objects(ptr);

  cl1->setId("1");
  cl2->setId("2");
  cl3->setId("3");

  cl1->setRate(1);
  cl2->setRate(2);
  cl3->setRate(10);

  QObject::connect(cl1, &Objects::sendData, ptr.data(),
                   &RemoteMinimalReplica::process);
  QObject::connect(cl2, &Objects::sendData, ptr.data(),
                   &RemoteMinimalReplica::process);
  QObject::connect(cl3, &Objects::sendData, ptr.data(),
                   &RemoteMinimalReplica::process);

  QObject::connect(ptr.data(), &RemoteMinimalReplica::sendData, cl1,
                   &Objects::printData);
  QObject::connect(ptr.data(), &RemoteMinimalReplica::sendData, cl2,
                   &Objects::printData);
  QObject::connect(ptr.data(), &RemoteMinimalReplica::sendData, cl3,
                   &Objects::printData);

  QEventLoop loop;
  QObject::connect(ptr.data(), &RemoteMinimalReplica::initialized, &loop,
                   &QEventLoop::quit);
  loop.exec();
  cl1->run();
  cl2->run();
  cl3->run();

  return a.exec();
}
