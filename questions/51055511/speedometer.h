#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <qwt_dial.h>

class SpeedoMeter : public QwtDial {
public:
  SpeedoMeter(QWidget *parent = nullptr);

protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void paintEvent(QPaintEvent *event);

private:
  QString d_label;
};

#endif // SPEEDOMETER_H
