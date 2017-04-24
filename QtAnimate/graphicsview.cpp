#include "graphicsview.h"

#include <QPainterPath>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QDebug>

#include "ellipseobject.h"

GraphicsView::GraphicsView(QWidget *parent):QGraphicsView(parent)
{

    QGraphicsScene *scene = new QGraphicsScene(this);

    scene->setBackgroundBrush(Qt::black);

    group = new QParallelAnimationGroup(this);

    setCacheMode(QGraphicsView::CacheBackground);

    int p = 180;
    QPointF center(scene->sceneRect().center());

    qreal R = 110.0;
    qreal r = 90.0;

    int number_of_items = 10;

    QPainterPath path1, path2;

    path1.addEllipse(center, R, R);
    path2.addEllipse(center, r, r);

    scene->addPath(path1-path2, QPen(Qt::white), QBrush(Qt::green));


    QList<QPointF> points;

    for(int i=0; i < p; i++){
        points.append(0.5*(path1.pointAtPercent(1.0*i/(p-1)) + path2.pointAtPercent(1.0*i/(p-1))));
    }


    for(int i=0; i < number_of_items; i++){
        EllipseObject *item = new EllipseObject;
        QPropertyAnimation *animation = new QPropertyAnimation(item, "pos");
        for(int j = 0; j < points.count(); j++){
            animation->setKeyValueAt( 1.0*j/(points.count()-1),
                                      points[((i*(p/number_of_items) +j) % points.count())]);
        }
        animation->setDuration(5000);
        group->addAnimation(animation);
        scene->addItem(item);
    }
    group->start();
    connect(group, &QParallelAnimationGroup::finished,[=](){
        group->start();
    });



    setScene(scene);
}

void GraphicsView::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    group->stop();
}

