#include "nativemessenger.h"

#include <QCoreApplication>
#include <QSocketNotifier>

NativeMessenger::NativeMessenger(QObject *parent) : QObject(parent)
{
    m_qin.open(stdin, QIODevice::ReadOnly | QIODevice::Unbuffered);
    m_qout.open(stdout, QIODevice::WriteOnly);

    QSocketNotifier *m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated, this, &NativeMessenger::readyRead);
}

void NativeMessenger::sendMessage(const QByteArray &message){
    quint32 len = message.length();
    m_qout.write(reinterpret_cast<char *>(&len), sizeof(len));
    m_qout.write(message);
    m_qout.flush();
}

void NativeMessenger::readyRead(){
    m_qin.startTransaction();
    quint32 length = 0;
    qint64 rc = m_qin.read(reinterpret_cast<char *>(&length), sizeof(quint32));
    if (rc == -1) {
        m_qin.rollbackTransaction();
        return;
    }
    QByteArray message = m_qin.read(length);
    if (message.length() != int(length)) {
        m_qin.rollbackTransaction();
        return;
    }
    if (message.isEmpty()) {
        m_qin.rollbackTransaction();
        return;
    }
    m_qin.commitTransaction();
    Q_EMIT messageChanged(message);
}
