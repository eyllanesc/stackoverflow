#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
#include <QDrag>
#include <QMimeData>
#include <QPainter>

class ListWidget : public QListWidget
{
protected:
    void startDrag(Qt::DropActions supportedActions){
        QDrag *drag = new QDrag(this);
        drag->setMimeData(model()->mimeData(selectedIndexes()));
        QPixmap pixmap(viewport()->visibleRegion().boundingRect().size());
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        for(QModelIndex index: selectedIndexes()){
            painter.drawPixmap(visualRect(index), viewport()->grab(visualRect(index)));
        }
        drag->setPixmap(pixmap);
        drag->setHotSpot(viewport()->mapFromGlobal(QCursor::pos()));
        drag->exec(supportedActions, Qt::MoveAction);
    }
};

#endif // LISTWIDGET_H
