#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
class QTimer;
class QLineEdit;

class Counter : public QObject {
  Q_OBJECT
public:
  explicit Counter(QLineEdit *setterSec, QLineEdit *setterMin,
                   QObject *parent = nullptr);
  QTimer *timer;
  QLineEdit *setterSec;
  QLineEdit *setterMin;
  int count;
signals:
  void showCountSec(const QString &count);
  void showCountMin(int count);

public slots:
  void decCount();
  void start();
  void stop();
  void set();
};

#endif // COUNTER_H
