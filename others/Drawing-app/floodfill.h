#ifndef _TROFIMOV_FLOOD_FILL_H_
#define _TROFIMOV_FLOOD_FILL_H_

#include <QImage>

#include <vector>

namespace DrawApp {
std::vector<QPoint> floodFill(QImage *image, const QPoint &pos,
                              const QRgb &newColor);
}

#endif
