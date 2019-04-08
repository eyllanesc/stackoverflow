#ifndef TICKDATA_H
#define TICKDATA_H

#include <QThread>

class TickData : public QThread {
public:
  TickData();
  ~TickData();
  void setSpeed(int s);
  void set_callBack_newData(std::function<void(void)> cbFun);
  void startData();
  void stopData();
  void run();

private:
  std::function<void(void)> cbFun;
  bool enable;
  bool startTick;
  int speed;
};

#endif // TICKDATA_H
