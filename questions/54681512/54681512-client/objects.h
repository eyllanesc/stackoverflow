#ifndef OBJECTS_H
#define OBJECTS_H

#include "rep_remoteminimal_replica.h"
#include <QObject>

class QTimer;

class Objects : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString id READ id WRITE setId)
  Q_PROPERTY(double rate READ rate WRITE setRate)
public:
  explicit Objects(QSharedPointer<RemoteMinimalReplica> ptr);
  ~Objects();
  double rate() const;
  void setRate(double rate);

  QString id() const;
  void setId(const QString &id);

signals:
  void sendData(const QString &, const QString &);

public slots:
  void printData(const QString &, const QString &);
  void process(const QString &);
  void triggerSendData();
  void run();

private:
  int m_global_server;
  QTimer *m_loop;
  double m_rate;
  QString m_id;
  QSharedPointer<RemoteMinimalReplica> reptr;
};

#endif // OBJECTS_H
