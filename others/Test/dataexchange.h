#ifndef DATAEXCHANGE_H
#define DATAEXCHANGE_H

#include <QObject>

class DataExchange : public QObject {
  Q_OBJECT
  Q_PROPERTY(
      bool serialOn READ get_serialOn WRITE set_serialOn NOTIFY serialOnChanged)
public:
  DataExchange(QObject *parent = 0);

  ~DataExchange();

  bool get_serialOn() const { return _serialOn; }

  void set_serialOn(bool value) {
    if (value != _serialOn) {
      _serialOn = value;
      emit serialOnChanged(_serialOn);
    }
  }

signals:
  void serialOnChanged(bool);

private:
  bool _serialOn;
};

#endif // DATAEXCHANGE_H
