#include <QApplication>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>

class GraphicsItemGroup: public QGraphicsItemGroup{
public:
    GraphicsItemGroup(QGraphicsItem * parent = 0):QGraphicsItemGroup(parent){
        setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    }
    QPainterPath shape() const
    {
        if(mShape.isEmpty())
            return QGraphicsItemGroup::shape();
        return mShape;
    }
    void setShape(const QPainterPath &shape){
        mShape = shape;
        update();
    }

private:
    QPainterPath mShape;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    w.setLayout(new QVBoxLayout);

    QGraphicsView view;
    QPushButton button("click me");

    w.layout()->addWidget(&view);
    w.layout()->addWidget(&button);

    view.setScene(new QGraphicsScene);
    GraphicsItemGroup group;
    view.scene()->addItem(&group);
    auto ellipse = new QGraphicsEllipseItem(QRectF(0, 0, 100, 100));
    ellipse->setBrush(Qt::red);
    auto rect = new QGraphicsRectItem(QRect(150, 150, 100, 100));
    rect->setBrush(Qt::blue);
    group.addToGroup(ellipse);
    group.addToGroup(rect);

    QObject::connect(&button, &QPushButton::clicked, [&group](){
        QPainterPath shape;
        if(group.shape().boundingRect() == group.boundingRect()){
            shape.addRect(0, 50, 250, 150);
        }
        group.setShape(shape);
    });

    w.show();
    return a.exec();
}

