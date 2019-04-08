#ifndef CONNECTUDP_H
#define CONNECTUDP_H

#include "datasourcemodel.h"

#include <QJsonArray>
#include <QObject>

class QUdpSocket;
class QQmlApplicationEngine;

class ConnectUdp : public QObject {
  Q_OBJECT

public:
  // constructors and destructors
  explicit ConnectUdp(QObject *parent = nullptr);
  ~ConnectUdp() = default;
  // declarations
  QJsonArray m_DataSourceArray;
  // functions
  void startUdpReceiver();
  void stopUdpReceiver();
  void initDataSources();

private:
  // declarations
  QUdpSocket *m_QUdpSocket;
  QQmlApplicationEngine *engine;
  // functions
  QJsonObject findValueFromJsonArray(QJsonArray, QString, int);

public:
  DataSourceModel m_DataSourceModel;
private slots:
  void processPendingDatagrams();
};

#endif // CONNECTUDP_H
