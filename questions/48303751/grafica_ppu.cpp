#include "grafica_ppu.h"

#include <QPainter>

Grafica_PPU::Grafica_PPU(const QString &ModuleName,
                         GraphicModuleData tmpInfoGrafiche, QPen Pen,
                         qreal tmpAlpha) {
  infoGrafiche = tmpInfoGrafiche;
  Penna = Pen;
  Testo = ModuleName;
  Alpha = tmpAlpha;
  setTransformOriginPoint(boundingRect().center());
  setRotation(Alpha);
}

QRectF Grafica_PPU::boundingRect() const {
  return QRectF(infoGrafiche.XC, infoGrafiche.YC, infoGrafiche.Width,
                infoGrafiche.Height);
}

void Grafica_PPU::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                        QWidget *) {
  painter->setPen(Penna);
  painter->setRenderHint(QPainter::Antialiasing); // Ottengo bordi senza
                                                  // spingoli
  painter->setRenderHint(
      QPainter::TextAntialiasing);   // Miglioro la lettura del testo ruotato
  painter->drawRect(boundingRect()); // Disegno il bordo di dimensioni scelte
  painter->translate(boundingRect().center());
  painter->rotate(-rotation());
  painter->translate(-boundingRect().center());
  painter->drawText(
      boundingRect(), Qt::AlignCenter,
      Testo); // Creo un testo avente dimensione uguale alla dimensione del
              // modulo, con il testo allineato al centro
}
