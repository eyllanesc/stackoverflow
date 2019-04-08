#include "lscurve.h"
#include <memory.h>
LSCurve::LSCurve() { double points[2048]; }
LSCurve::~LSCurve() {
  delete[] px;
  delete[] py;
}

bool LSCurve::reDraw() {
  this->QwtCurve->setSamples(px, py, index);
  return true;
}

bool LSCurve::addPoint(double x, double y) {
  px[index] = x;
  py[index] = y;
  index++;
  return true;
}

bool LSCurve::addPoint(double x[], double y[], int size) {
  for (int i = 0; i < size; i++) {
    if (index > 2048)
      return false;
    px[index] = x[i];
    py[index] = y[i];
    index++;
  }
  return true;
}

bool LSCurve::removePoint(void) {
  memset(px, 0, sizeof(px));
  memset(py, 0, sizeof(py));
  index = 0;
  return true;
}
