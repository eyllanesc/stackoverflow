#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsView>

class GraphicsPixmapItem : public QGraphicsPixmapItem {

public:
  GraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = 0)
      : QGraphicsPixmapItem(pixmap, parent) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
  }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) {
    if (!m_boundaryPath.isEmpty()) {
      QPainterPath path = mapFromScene(m_boundaryPath);
      if (!path.isEmpty())
        painter->setClipPath(path);
    }
    QGraphicsPixmapItem::paint(painter, option, widget);
  }

  QPainterPath boundaryPath() const { return m_boundaryPath; }
  void setBoundaryPath(const QPainterPath &boundaryPath) {
    m_boundaryPath = boundaryPath;
    update();
  }

private:
  QPainterPath m_boundaryPath;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QGraphicsView view;
  QGraphicsScene scene(0, 0, 600, 400);
  view.setScene(&scene);
  view.setBackgroundBrush(QBrush(Qt::gray));

  GraphicsPixmapItem *p_item = new GraphicsPixmapItem(QPixmap(":/ball.png"));
  p_item->setPos(100, 100);

  // Define the area that will be visible
  QPainterPath path;
  path.addRect(QRectF(100, 100, 400, 200));

  p_item->setBoundaryPath(path);
  scene.addItem(p_item);

  // the item is added to visualize the intersection
  QGraphicsPathItem *path_item =
      scene.addPath(path, QPen(Qt::black), QBrush(Qt::white));
  path_item->setZValue(-1);
  view.show();
  return a.exec();
}
