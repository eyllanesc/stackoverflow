#include "floodfill.h"

#include <vector>

namespace DrawApp {

struct FillPixelInfo {
  int y, xl, xr, dy;
};

#define PUSH(py, pxl, pxr, pdy)                                                \
  {                                                                            \
    struct FillPixelInfo p;                                                    \
    if (((py) + (pdy) >= 0) && ((py) + (pdy) < image.height())) {              \
      p.y = (py);                                                              \
      p.xl = (pxl);                                                            \
      p.xr = (pxr);                                                            \
      p.dy = (pdy);                                                            \
      stack.push_back(p);                                                      \
    }                                                                          \
  }

#define POP(py, pxl, pxr, pdy)                                                 \
  {                                                                            \
    struct FillPixelInfo p = stack.back();                                     \
    stack.pop_back();                                                          \
    (py) = p.y + p.dy;                                                         \
    (pxl) = p.xl;                                                              \
    (pxr) = p.xr;                                                              \
    (pdy) = p.dy;                                                              \
  }

std::vector<QPoint> floodFill(QImage *img, const QPoint &pos,
                              const QRgb &newColor) {
  std::vector<QPoint> res;

  QImage image(img->copy());
  int x(pos.x());
  int y(pos.y());
  const QRgb prevColor(image.pixel(x, y));
  std::vector<FillPixelInfo> stack;

  if ((0 <= x) && (x < image.width()) && (0 <= y) && (y < image.height())) {
    if (prevColor == newColor) {
      return res;
    }
    PUSH(y, x, x, 1);
    PUSH(y + 1, x, x, -1);
    int l, x1, x2, dy;
    while (!stack.empty()) {
      POP(y, x1, x2, dy);
      for (x = x1; (x >= 0) && image.pixel(x, y) == prevColor; --x) {
        image.setPixel(x, y, newColor);
        res.emplace_back(x, y);
      }
      if (x >= x1) {
        goto skip;
      }
      l = x + 1;
      if (l < x1) {
        PUSH(y, l, x1 - 1, -dy);
      }
      x = x1 + 1;
      do {
        for (; (x < image.width()) && image.pixel(x, y) == prevColor; ++x) {
          image.setPixel(x, y, newColor);
          res.emplace_back(x, y);
        }
        PUSH(y, l, x - 1, dy);
        if (x > x2 + 1) {
          PUSH(y, x2 + 1, x - 1, -dy);
        }
      skip:
        for (x++; x <= x2 && image.pixel(x, y) != prevColor; ++x) {
        }
        l = x;
      } while (x <= x2);
    }
  }

  return res;
}

} // namespace DrawApp
