#ifndef MINIMALSOURCE_H
#define MINIMALSOURCE_H

#include "rep_remoteminimal_source.h"
#include <QObject>

class MinimalSource : public RemoteMinimalSource {
  Q_OBJECT
public:
  MinimalSource(QObject *parent = nullptr);
  ~MinimalSource() override;

public slots:
  void printData(const QString &data) override;
  void process(const QString &data, const QString &id) override;
  void triggerSendData() override;

private:
  int m_global_server;
};

#endif // MINIMALSOURCE_H
