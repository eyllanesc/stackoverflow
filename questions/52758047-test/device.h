#ifndef DEVICE_H
#define DEVICE_H

#include <QWidget>

class Device : public QWidget {
  Q_OBJECT
public:
  explicit Device(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // DEVICE_H