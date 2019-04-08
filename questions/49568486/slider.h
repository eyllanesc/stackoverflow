#ifndef SLIDER_H
#define SLIDER_H

#include <QMouseEvent>
#include <QSlider>
#include <QStyle>
#include <QStyleOptionSlider>

class Slider : public QSlider {
public:
  using QSlider::QSlider;
  // https://github.com/openwebos/qt/blob/master/src/gui/widgets/qslider.cpp#L100
  int pixelPosToRangeValue(int pos) const {
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect gr = style()->subControlRect(QStyle::CC_Slider, &opt,
                                       QStyle::SC_SliderGroove, this);
    QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt,
                                       QStyle::SC_SliderHandle, this);
    int sliderMin, sliderMax, sliderLength;

    if (orientation() == Qt::Horizontal) {
      sliderLength = sr.width();
      sliderMin = gr.x();
      sliderMax = gr.right() - sliderLength + 1;
    } else {
      sliderLength = sr.height();
      sliderMin = gr.y();
      sliderMax = gr.bottom() - sliderLength + 1;
    }
    return QStyle::sliderValueFromPosition(
        minimum(), maximum(), pos - sliderMin, sliderMax - sliderMin,
        opt.upsideDown);
  }

  bool inside(QPoint p) {
    QRect r(mapToGlobal(QPoint(0, -height())), QSize(width(), 2 * height()));
    return r.contains(p);
  }
};

#endif // SLIDER_H
