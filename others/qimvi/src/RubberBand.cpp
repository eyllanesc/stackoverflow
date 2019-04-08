#include "RubberBand.h"
#include <QGraphicsView>
#include <QMouseEvent>

RubberBand::RubberBand(QObject *parent)
    : QObject(parent), rubberBand(QRubberBand::Rectangle, nullptr),
      pixmapItem(nullptr) {}

RubberBand::~RubberBand() {}

/**
 * @brief Ustawia lub zmienia obraz nad którym będą śledzone zdarzenia myszy.
 */
void RubberBand::SetPixmapItem(QGraphicsPixmapItem *newItem) {
  rubberBand.hide(); // Anuluje zaznaczenie, jeżeli jakieś istniało.
  pixmapItem = newItem;
  if (MousePositionTracker)
    MousePositionTracker(QPoint());
  if (SelectionTracker)
    SelectionTracker(QRect());
}

/**
 * @brief Metoda nasłuchująca zdarzeń pochodzących z QGraphicsView.
 *		  Zdarzenia naciśnięć i poruszania myszą są przetwarzane dalej.
 */
bool RubberBand::eventFilter(QObject *watched, QEvent *event) {
  if (pixmapItem == nullptr)
    return QObject::eventFilter(watched, event);

  switch (event->type()) {
  case QEvent::MouseButtonPress:
    mousePressEvent(reinterpret_cast<QMouseEvent *>(event));
    return true;
  case QEvent::MouseMove:
    mouseMoveEvent(reinterpret_cast<QMouseEvent *>(event));
    return true;
  case QEvent::Wheel:
    mouseWheelEvent(reinterpret_cast<QWheelEvent *>(event));
    return true;
  default:
    return QObject::eventFilter(watched, event);
  }
}

/**
 * @brief Metoda obsługująca zdarzenie kręcenia rolką myszy.
 */
void RubberBand::mouseWheelEvent(QWheelEvent *event) const {
  if (WheelTracker) {
    auto posItem = RelativeClippedCoordinates(event->globalPos());
    WheelTracker(event->delta(), posItem);
  }
}

/**
 * @brief Metoda obsługująca zdarzenie wciśnięcia przycisku myszy.
 */
void RubberBand::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() != Qt::LeftButton)
    return;
  if (rubberBand.isVisible()) {
    // Anuluje zaznaczenie jeśli jest aktywne.
    rubberBand.hide();
    return;
  }

  auto posItem = RelativeClippedCoordinates(event->globalPos());

  origin = CoordinatesItemToGlobal(pixmapItem, posItem);
  selectionRect.setTopLeft(posItem);

  rubberBand.setGeometry(QRect(origin, QSize()));
  rubberBand.show();
}

/**
 * @brief Metoda obsługująca zdarzenie poruszania myszą.
 */
void RubberBand::mouseMoveEvent(QMouseEvent *event) {
  auto posItem = RelativeClippedCoordinates(event->globalPos());

  if (MousePositionTracker)
    MousePositionTracker(posItem);
  if (event->buttons() != Qt::LeftButton)
    return;
  rubberBand.setGeometry(
      QRect(origin, CoordinatesItemToGlobal(pixmapItem, posItem)).normalized());

  selectionRect.setBottomRight(posItem);
  if (SelectionTracker)
    SelectionTracker(GetSelection());
}

/**
 * @brief Informuje, czy zostało coś zaznaczone.
 */
bool RubberBand::IsSelectionActive() const { return rubberBand.isVisible(); }

/**
 * @brief Zwraca prostokątną powierzchnię zaznaczenia.
 */
QRect RubberBand::GetSelection() const {
  return selectionRect.normalized().toRect();
}

/**
 * @brief Zwraca relatywne położenie myszy względem obrazu dla danej globalnej
 * pozycji kursora myszy.
 */
QPoint RubberBand::RelativeClippedCoordinates(QPoint globalPos) const {
  auto posItem = CoordinatesGlobalToItem(pixmapItem, globalPos);
  auto bounds = QRect(QPoint(), pixmapItem->pixmap().size());
  // Współrzędne myszy są przycinane do rozmiaru obrazu.
  return ClipCoordinatesInRect(posItem, bounds).toPoint();
}

/**
 * @brief Przycina współrzędne punktu tak, aby zawsze były w granicach
 * prostokąta.
 * @param point Przycinany punkt.
 * @param clippingBounds Prostokąt ograniczający.
 */
QPointF RubberBand::ClipCoordinatesInRect(QPointF point,
                                          QRectF clippingBounds) {
  // Jeżeli punkt już znajduje się w prostokącie to nie ma potrzeby go
  // przycinać.
  if (clippingBounds.contains(point))
    return point;

  return QPointF(
      std::max(std::min(point.x(), clippingBounds.width()), clippingBounds.x()),
      std::max(std::min(point.y(), clippingBounds.height()),
               clippingBounds.y()));
}

/**
 * @brief Mapuje współrzędne względem danego obiektu QGraphicsItem na
 * współrzędne globalne.
 */
QPoint RubberBand::CoordinatesItemToGlobal(QGraphicsItem *item,
                                           QPointF posItem) {
  auto view = item->scene()->views().first();

  auto posScene = item->mapToScene(posItem);
  auto posViewport = view->mapFromScene(posScene);
  auto posGlobal = view->viewport()->mapToGlobal(posViewport);
  return posGlobal;
}

/**
 * @brief Mapuje współrzędne globalne na współrzędne względem danego obiektu
 * QGraphicsItem.
 */
QPointF RubberBand::CoordinatesGlobalToItem(QGraphicsItem *item,
                                            QPoint posGlobal) {
  auto view = item->scene()->views().first();

  auto posViewport = view->viewport()->mapFromGlobal(posGlobal);
  auto posScene = view->mapToScene(posViewport);
  auto posItem = item->mapFromScene(posScene);
  return posItem;
}
