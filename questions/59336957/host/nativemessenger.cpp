#include "nativemessenger.h"

#include <QCoreApplication>
#ifdef Q_OS_WIN
#include <QWinEventNotifier>
#include <windows.h>
#else
#include <QSocketNotifier>
#endif
NativeMessenger::NativeMessenger(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_WIN
    // https://developer.chrome.com/apps/nativeMessaging#native-messaging-debugging
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    m_qin.open(stdin, QIODevice::ReadOnly | QIODevice::Unbuffered);
    m_qout.open(stdout, QIODevice::WriteOnly);

#ifdef Q_OS_WIN
    QWinEventNotifier *m_notifier = new QWinEventNotifier(GetStdHandle(STD_INPUT_HANDLE));
    connect(m_notifier, &QWinEventNotifier::activated, this, &NativeMessenger::readyRead);
#else
    QSocketNotifier *m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated, this, &NativeMessenger::readyRead);
#endif
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
