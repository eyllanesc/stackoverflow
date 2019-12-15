#ifndef NATIVEMESSENGER_H
#define NATIVEMESSENGER_H

#include <QObject>
#include <QFile>

class NativeMessenger : public QObject
{
    Q_OBJECT
public:
    explicit NativeMessenger(QObject *parent = nullptr);
public Q_SLOTS:
    void sendMessage(const QByteArray & message);
Q_SIGNALS:
    void messageChanged(const QByteArray & message);
private Q_SLOTS:
    void readyRead();
private:
    QFile m_qin;
    QFile m_qout;
};

#endif // NATIVEMESSENGER_H
