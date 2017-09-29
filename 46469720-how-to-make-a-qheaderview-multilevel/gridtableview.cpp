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
        connect(header, &GridTableHeaderView::sectionPressed, this, &GridTableView::horizontalHeaderSectionPressed);
    }
    else{
        header = new GridTableHeaderView(orientation, model()->rowCount(), levels);
        setVerticalHeader(header);
        connect(header, &GridTableHeaderView::sectionPressed,this, &GridTableView::verticalHeaderSectionPressed);
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
