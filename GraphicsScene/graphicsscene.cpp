#include "graphicsscene.h"

#include <QDebug>

GraphicsScene::GraphicsScene(QObject *parent): QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    qDebug() << Q_FUNC_INFO << mouseEvent ->scenePos();
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    QPointF point = mouseEvent->scenePos();
    emit changedMousePosition(point);
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    mousePoint = mouseEvent->scenePos();

    mousePoints.append(mouseEvent->scenePos());

    if(mousePoints.size() == 2)
    {
        QColor color;
        color.setRgb(128, 0, 255);
        QPen pen;
        pen.setColor(color);
        pen.setWidth(20);
        pen.setCapStyle(Qt::RoundCap);
        this->addLine(mousePoints.at(0).x(), mousePoints.at(0).y(), mousePoints.at(1).x(), mousePoints.at(1).y(), pen);
        update();

        mousePoints.clear();
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    mousePoint = mouseEvent->scenePos();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


QPointF GraphicsScene::getMousePoint(void)
{
    return mousePoint;
}
