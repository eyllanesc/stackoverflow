#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QStyleOptionGraphicsItem>

class GraphicsPixmapItem : public QGraphicsPixmapItem {
public:
  GraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = 0)
      : QGraphicsPixmapItem(pixmap, parent) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
  }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *) {
    painter->setRenderHint(QPainter::SmoothPixmapTransform,
                           (transformationMode() == Qt::SmoothTransformation));
    painter->drawPixmap(offset(), pixmap());
    if (option->state & QStyle::State_Selected) {
      painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
      painter->setBrush(Qt::NoBrush);
      painter->drawPath(shape());
    }
  }
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QGraphicsView w;
  QGraphicsScene scene;
  GraphicsPixmapItem *item = new GraphicsPixmapItem(QPixmap(":/image.png"));
  scene.addItem(item);
  w.setScene(&scene);
  w.show();

  return a.exec();
}
