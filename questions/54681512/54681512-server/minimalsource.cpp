#include "minimalsource.h"

MinimalSource::MinimalSource(QObject *parent)
    : RemoteMinimalSource(parent), m_global_server(0) {}

MinimalSource::~MinimalSource() {}

void MinimalSource::printData(const QString &data) { Q_UNUSED(data); }

void MinimalSource::process(const QString &data, const QString &id) {
  m_global_server++;
  emit sendData(data + ":" + QString::number(m_global_server), id);
}

void MinimalSource::triggerSendData() {}
