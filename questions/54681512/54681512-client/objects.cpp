#include "objects.h"

#include <QDebug>
#include <QTimer>

Objects::Objects(QSharedPointer<RemoteMinimalReplica> ptr)
    : QObject(Q_NULLPTR), m_global_server(0), reptr(ptr) {
  m_loop = new QTimer(this);
}
Objects::~Objects() {}

void Objects::printData(const QString &data, const QString &id) {
  if (id == m_id)
    qDebug() << "[" << m_id << "]:" << data;
}

void Objects::process(const QString &data) {
  emit sendData(data + ":processed", m_id);
}

void Objects::run() {
  connect(m_loop, &QTimer::timeout, this, &Objects::triggerSendData);
  m_loop->setInterval(static_cast<int>(1000 / m_rate));
  m_loop->start();
}

QString Objects::id() const { return m_id; }

void Objects::setId(const QString &id) { m_id = id; }

double Objects::rate() const { return m_rate; }

void Objects::setRate(double rate) { m_rate = rate; }

void Objects::triggerSendData() {
  m_global_server++;
  emit sendData(QString("test:%1:%2").arg(m_id).arg(m_global_server), m_id);
}
