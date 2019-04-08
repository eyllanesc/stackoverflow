#ifndef LOGICCLASS_H
#define LOGICCLASS_H

#include <QObject>

class LogicClass : public QObject {
  Q_OBJECT
public:
  explicit LogicClass(QObject *parent = 0);

signals:

public slots:
  void on_click_slot();
};

#endif // LOGICCLASS_H
