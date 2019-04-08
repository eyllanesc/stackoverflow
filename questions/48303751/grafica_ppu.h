#ifndef GRAFICA_PPU_H
#define GRAFICA_PPU_H

#include <QGraphicsRectItem>
#include <QPen>

struct GraphicModuleData {
  int XC;
  int YC;
  int Width;
  int Height;
};

class Grafica_PPU : public QGraphicsItem {
public:
  Grafica_PPU(const QString &ModuleName, GraphicModuleData tmpInfoGrafiche,
              QPen Pen, qreal tmpAlpha);
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

private:
  GraphicModuleData infoGrafiche;
  qreal Alpha, xc, yc;
  QString Testo;
  QPen Penna;
};

#endif // GRAFICA_PPU_H
