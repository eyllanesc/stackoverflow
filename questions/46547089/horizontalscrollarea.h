#ifndef HORIZONTALSCROLLAREA_H
#define HORIZONTALSCROLLAREA_H

#include <QGridLayout>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>

#include <QDebug>

class HorizontalScrollArea : public QScrollArea
{
    QWidget *contentWidget;
    QGridLayout *grid;
    int nRows;
    int nColumns;
public:
    HorizontalScrollArea(int rows, int cols, QWidget *parent = Q_NULLPTR)
        :QScrollArea(parent), nRows(rows), nColumns(cols)
    {
        setWidgetResizable(true);
        contentWidget = new QWidget(this);
        setWidget(contentWidget);
        grid = new QGridLayout(contentWidget);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    void addWidget(QWidget *w, int row, int col){
        grid->addWidget(w, row, col);
        adaptSize();
    }

    int columnCount() const{
        if(grid->count() == 0){
            return 0;
        }
        return grid->columnCount();
    }

private:
    void adaptSize(){
        if(columnCount() >= nColumns ){
            int w = 1.0*(width() - grid->horizontalSpacing()*(nColumns+1.6))/nColumns;
            int wCorrected = w*columnCount() + grid->horizontalSpacing()*(columnCount()+2);
            contentWidget->setFixedWidth(wCorrected);
        }
        contentWidget->setFixedHeight(viewport()->height());
    }
protected:
    void resizeEvent(QResizeEvent *event){
        QScrollArea::resizeEvent(event);
        adaptSize();
    }
};

#endif // HORIZONTALSCROLLAREA_H
