#include <QDebug>
#include <QString>
#include <QThread>
#include <QUrl>

#include <zmq.hpp>

int main(void) {

  QString m_ServerIP = QString("127.0.0.1");
  int m_ServerPort = 5555;

  qDebug() << QString("Server IP Address determined to be: %1").arg(m_ServerIP);

  QUrl url;
  url.setScheme("tcp");
  url.setHost(m_ServerIP);
  url.setPort(m_ServerPort);

  zmq::context_t context(1);
  zmq::socket_t subscriber(context, ZMQ_SUB);
  subscriber.connect(url.toString().toStdString());
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

  while (true) {
    zmq_msg_t in_msg;
    zmq_msg_init(&in_msg);
    zmq::message_t message;
    subscriber.recv(&message);
    qDebug() << QString("Message Size: %1").arg(message.size());
    QByteArray ba(static_cast<char *>(message.data()), message.size());
    qDebug() << "message" << ba;
    QThread::sleep(1);
  }
}
