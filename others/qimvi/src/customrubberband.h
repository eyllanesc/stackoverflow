#ifndef CUSTOMRUBBERBAND_H
#define CUSTOMRUBBERBAND_H

#include <QRubberBand>

class CustomRubberBand : public QRubberBand {
public:
  CustomRubberBand(Shape s, QWidget *p = 0);

protected:
  void paintEvent(QPaintEvent *);
};

#endif // CUSTOMRUBBERBAND_H
