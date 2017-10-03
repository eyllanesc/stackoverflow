#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QGridLayout>
#include <QScrollArea>
#include <QScrollBar>

#include <QDebug>

class ScrollArea : public QScrollArea
{
    QWidget *contentWidget;
    QGridLayout *grid;
    QSize _size;
public:
    ScrollArea(int nRows, int nCols, QSize sizeWidget, QWidget *parent = Q_NULLPTR)
        :QScrollArea(parent), _size(sizeWidget)
    {
        setWidgetResizable(true);
        contentWidget = new QWidget(this);
        setWidget(contentWidget);
        grid = new QGridLayout(contentWidget);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QSize s(nCols*sizeWidget.width() + (nCols+1)*grid->horizontalSpacing(),
                nRows*sizeWidget.height() + nRows*grid->verticalSpacing());

        contentWidget->setFixedHeight(s.height());
        setFixedSize(s + QSize(grid->horizontalSpacing(), horizontalScrollBar()->height()));
        viewport()->setFixedSize(s);
    }

    void addWidget(QWidget *w, int row, int col){
        grid->addWidget(w, row, col);
        w->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        w->setFixedSize(_size);
    }

    int columnCount() const{
        return grid->columnCount();
    }
};

#endif // SCROLLAREA_H
