#include "gridtableheaderview.h"
#include "gridtableview.h"

#include <QStandardItemModel>

GridTableView::GridTableView(QWidget *parent) : QTableView(parent)
{

}

void GridTableView::setGridHeaderview(Qt::Orientation orientation, int levels)
{
    GridTableHeaderView *header;
    if(orientation == Qt::Horizontal){
        header = new GridTableHeaderView(orientation, levels, model()->columnCount());
        setHorizontalHeader(header);
#if QT_VERSION >= 0x050000
        connect(header, &GridTableHeaderView::sectionPressed, this, &GridTableView::horizontalHeaderSectionPressed);
#else
        connect(header, SIGNAL(sectionPressed(int,int)), this, SLOT(horizontalHeaderSectionPressed(int,int)));
#endif
    }
    else{
        header = new GridTableHeaderView(orientation, model()->rowCount(), levels);
        setVerticalHeader(header);
#if QT_VERSION >= 0x050000
        connect(header, &GridTableHeaderView::sectionPressed,this, &GridTableView::verticalHeaderSectionPressed);
#else
        connect(header, SIGNAL(sectionPressed(int, int)), this, SLOT(verticalHeaderSectionPressed(int,int)));
#endif
    }
}

GridTableHeaderView *GridTableView::gridHeaderview(Qt::Orientation orientation)
{
    GridTableHeaderView  *header;
    if(orientation == Qt::Horizontal){
        header = qobject_cast<GridTableHeaderView*>(horizontalHeader());
    }
    else{
        header = qobject_cast<GridTableHeaderView*>(verticalHeader());
    }
    return header;

}

void GridTableView::horizontalHeaderSectionPressed(int beginSection, int endSection)
{
    clearSelection();
    QAbstractItemView::SelectionMode oldSelectionMode = selectionMode();
    setSelectionMode(QAbstractItemView::MultiSelection);
    for (int i=beginSection;i<endSection+1;++i)
        selectColumn(i);
    setSelectionMode(oldSelectionMode);
}

void GridTableView::verticalHeaderSectionPressed(int beginSection, int endSection)
{
    clearSelection();
    QAbstractItemView::SelectionMode oldSelectionMode = selectionMode();
    setSelectionMode(QAbstractItemView::MultiSelection);
    for (int i=beginSection;i<endSection+1;++i)
        selectRow(i);
    setSelectionMode(oldSelectionMode);
}
