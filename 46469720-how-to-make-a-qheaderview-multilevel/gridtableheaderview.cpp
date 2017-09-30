#include "gridtableheadermodel.h"
#include "gridtableheaderview.h"

#include <QMouseEvent>
#include <QPainter>

GridTableHeaderView::GridTableHeaderView(Qt::Orientation orientation, int rows, int columns, QWidget *parent)
    : QHeaderView(orientation, parent)
{
    QSize baseSectionSize;
    if (orientation == Qt::Horizontal){
        baseSectionSize.setWidth(defaultSectionSize());
        baseSectionSize.setHeight(20);
    }
    else{
        baseSectionSize.setWidth(50);
        baseSectionSize.setHeight(defaultSectionSize());
    }

    GridTableHeaderModel *model = new GridTableHeaderModel(rows,columns);
    for (int row=0;row<rows;++row)
        for (int col=0;col<columns;++col)
            model->setData(model->index(row, col), baseSectionSize, Qt::SizeHintRole);

    setModel(model);
#if QT_VERSION >= 0x050000
    connect(this, &QHeaderView::sectionResized, this, &GridTableHeaderView::onSectionResized);
#else
    connect(this, SIGNAL(sectionResized(int,int,int)), this, SLOT(onSectionResized(int,int,int)));
#endif
}

GridTableHeaderView::~GridTableHeaderView()
{

}

void GridTableHeaderView::setCellLabel(int row, int column, const QString &label)
{
    model()->setData(model()->index(row, column), label, Qt::DisplayRole);
}

void GridTableHeaderView::setCellBackgroundColor(int row, int column, const QColor &color)
{
    model()->setData(model()->index(row, column), color, Qt::BackgroundRole);
}

void GridTableHeaderView::setCellForegroundColor(int row, int column, const QColor &color)
{
    model()->setData(model()->index(row, column), color, Qt::ForegroundRole);
}

QModelIndex GridTableHeaderView::indexAt(const QPoint& pos)
{
    const GridTableHeaderModel* tblModel = qobject_cast<GridTableHeaderModel*>(model());
    const int rows = tblModel->rowCount();
    const int cols = tblModel->columnCount();
    int logicalIdx = logicalIndexAt(pos);
    int delta = 0;
    if (orientation() == Qt::Horizontal){
        for (int row = 0;row < rows; ++row)
        {
            QModelIndex cellIndex = tblModel->index(row,logicalIdx);
            delta += cellIndex.data(Qt::SizeHintRole).toSize().height();
            if (pos.y() <= delta) return cellIndex;
        }
    }
    else{
        for (int col=0;col< cols;++col){
            QModelIndex cellIndex = tblModel->index(logicalIdx,col);
            delta += cellIndex.data(Qt::SizeHintRole).toSize().width();
            if (pos.x() <= delta) return cellIndex;
        }
    }

    return QModelIndex();
}

void GridTableHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    const GridTableHeaderModel* tblModel = qobject_cast<GridTableHeaderModel*>(this->model());
    const int level = ( orientation() == Qt::Horizontal) ? tblModel->rowCount() : tblModel->columnCount();
    for (int i=0; i < level; ++i) {
        QModelIndex cellIndex = (orientation() == Qt::Horizontal) ? tblModel->index(i, logicalIndex): tblModel->index(logicalIndex, i);
        QSize cellSize=cellIndex.data(Qt::SizeHintRole).toSize();
        QRect sectionRect(rect);

        // set position of the cell
        if (orientation() == Qt::Horizontal)
            sectionRect.setTop(rowSpanSize(logicalIndex,0,i)); // distance from 0 to i-1 rows
        else
            sectionRect.setLeft(columnSpanSize(logicalIndex,0,i));

        sectionRect.setSize(cellSize);

        // check up span column or row
        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);
        if (colSpanIdx.isValid()) {
            int colSpanFrom = colSpanIdx.column();
            int colSpanCnt  = colSpanIdx.data(GridTableHeaderModel::ColumnSpanRole).toInt();
            int colSpanTo   = colSpanFrom + colSpanCnt - 1;
            int colSpan     = columnSpanSize(cellIndex.row(), colSpanFrom, colSpanCnt);
            if (orientation() == Qt::Horizontal)
                sectionRect.setLeft(sectionViewportPosition(colSpanFrom));
            else {
                sectionRect.setLeft(columnSpanSize(logicalIndex, 0, colSpanFrom));
                i = colSpanTo;
            }

            sectionRect.setWidth(colSpan);

            // check up  if the column span index has row span
            QVariant subRowSpanData = colSpanIdx.data(GridTableHeaderModel::RowSpanRole);
            if (subRowSpanData.isValid()) {
                int subRowSpanFrom = colSpanIdx.row();
                int subRowSpanCnt  = subRowSpanData.toInt();
                int subRowSpanTo   = subRowSpanFrom+subRowSpanCnt-1;
                int subRowSpan     = rowSpanSize(colSpanFrom,subRowSpanFrom,subRowSpanCnt);
                if (orientation() == Qt::Vertical)
                    sectionRect.setTop(sectionViewportPosition(subRowSpanFrom));
                else {
                    sectionRect.setTop(rowSpanSize(colSpanFrom,0,subRowSpanFrom));
                    i = subRowSpanTo;
                }
                sectionRect.setHeight(subRowSpan);
            }
            cellIndex=colSpanIdx;
        }
        if (rowSpanIdx.isValid()) {
            int rowSpanFrom = rowSpanIdx.row();
            int rowSpanCnt  = rowSpanIdx.data(GridTableHeaderModel::RowSpanRole).toInt();
            int rowSpanTo   = rowSpanFrom+rowSpanCnt-1;
            int rowSpan     = rowSpanSize(cellIndex.column(),rowSpanFrom,rowSpanCnt);
            if (orientation() == Qt::Vertical)
                sectionRect.setTop(sectionViewportPosition(rowSpanFrom));
            else{
                sectionRect.setTop(rowSpanSize(logicalIndex,0,rowSpanFrom));
                i = rowSpanTo;
            }
            sectionRect.setHeight(rowSpan);

            // check up if the row span index has column span
            QVariant subColSpanData = rowSpanIdx.data(GridTableHeaderModel::ColumnSpanRole);
            if (subColSpanData.isValid()){
                int subColSpanFrom = rowSpanIdx.column();
                int subColSpanCnt  = subColSpanData.toInt();
                int subColSpanTo   = subColSpanFrom+subColSpanCnt-1;
                int subColSpan     = columnSpanSize(rowSpanFrom,subColSpanFrom,subColSpanCnt);
                if (orientation() == Qt::Horizontal)
                    sectionRect.setLeft(sectionViewportPosition(subColSpanFrom));
                else{
                    sectionRect.setLeft(columnSpanSize(rowSpanFrom,0,subColSpanFrom));
                    i = subColSpanTo;
                }
                sectionRect.setWidth(subColSpan);
            }
            cellIndex=rowSpanIdx;
        }

        // draw section with style
        QStyleOptionHeader opt;
        initStyleOption(&opt);
        opt.textAlignment = Qt::AlignCenter;
        opt.iconAlignment = Qt::AlignVCenter;
        opt.section = logicalIndex;
        opt.text = cellIndex.data(Qt::DisplayRole).toString();
        opt.rect = sectionRect;

        QVariant bg = cellIndex.data(Qt::BackgroundRole);
        QVariant fg = cellIndex.data(Qt::ForegroundRole);
        if (bg.canConvert<QBrush>())
        {
            opt.palette.setBrush(QPalette::Button, bg.value<QBrush>());
            opt.palette.setBrush(QPalette::Window, bg.value<QBrush>());
        }
        if (fg.canConvert<QBrush>())
        {
            opt.palette.setBrush(QPalette::ButtonText, fg.value<QBrush>());
        }

        painter->save();
        style()->drawControl(QStyle::CE_Header, &opt, painter, this);
        painter->restore();
    }
}

QSize GridTableHeaderView::sectionSizeFromContents(int logicalIndex) const
{
    const GridTableHeaderModel* tblModel = qobject_cast<const GridTableHeaderModel*>(this->model());
    const int level = (orientation() == Qt::Horizontal) ? tblModel->rowCount() : tblModel->columnCount();

    QSize size = QHeaderView::sectionSizeFromContents(logicalIndex);
    for (int i=0;i< level;++i) {
        QModelIndex cellIndex = (orientation() == Qt::Horizontal)?tblModel->index(i,logicalIndex):tblModel->index(logicalIndex,i);
        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);
        size = cellIndex.data(Qt::SizeHintRole).toSize();

        if (colSpanIdx.isValid()){
            int colSpanFrom = colSpanIdx.column();
            int colSpanCnt     = colSpanIdx.data(GridTableHeaderModel::ColumnSpanRole).toInt();
            int colSpanTo   = colSpanFrom + colSpanCnt -1;
            size.setWidth(columnSpanSize(colSpanIdx.row(),colSpanFrom,colSpanCnt));
            if (orientation() == Qt::Vertical) i = colSpanTo;
        }
        if (rowSpanIdx.isValid()) {
            int rowSpanFrom = rowSpanIdx.row();
            int rowSpanCnt  = rowSpanIdx.data(GridTableHeaderModel::RowSpanRole).toInt();
            int rowSpanTo   = rowSpanFrom + rowSpanCnt-1;
            size.setHeight(rowSpanSize(rowSpanIdx.column(),rowSpanFrom,rowSpanCnt));
            if (orientation() == Qt::Horizontal) i = rowSpanTo;
        }
    }
    return size;
}

void GridTableHeaderView::setRowHeight(int row, int height)
{
    GridTableHeaderModel* m = qobject_cast<GridTableHeaderModel*>(model());
    const int cols = m->columnCount();
    for (int col=0; col<cols; ++col) {
        QSize sz = m->index(row,col).data(Qt::SizeHintRole).toSize();
        sz.setHeight(height);
        m->setData(m->index(row,col), sz, Qt::SizeHintRole);
    }
    if (orientation() == Qt::Vertical)
        resizeSection(row, height);
}

void GridTableHeaderView::setColumnWidth(int col, int width)
{
    GridTableHeaderModel* m = qobject_cast<GridTableHeaderModel*>(model());
    const int rows = m->rowCount();
    for (int row=0;row<rows;++row){
        QSize sz = m->index(row,col).data(Qt::SizeHintRole).toSize();
        sz.setWidth(width);
        m->setData(m->index(row,col), sz, Qt::SizeHintRole);
    }
    if (orientation() == Qt::Horizontal)
        resizeSection(col, width);
}

void GridTableHeaderView::setSpan(int row, int column, int rowSpanCount, int columnSpanCount)
{
    GridTableHeaderModel* md = qobject_cast<GridTableHeaderModel*>(model());
    QModelIndex idx = md->index(row,column);
    if (rowSpanCount > 0)
        md->setData(idx,rowSpanCount,GridTableHeaderModel::RowSpanRole);
    if (columnSpanCount > 0)
        md->setData(idx,columnSpanCount, GridTableHeaderModel::ColumnSpanRole);
}

void GridTableHeaderView::setSpan(int row, int column)
{
    if(orientation() == Qt::Horizontal)
        setSpan(row, column, model()->rowCount(), 1);
    else
        setSpan(row, column, 1, model()->columnCount());
}

QModelIndex GridTableHeaderView::columnSpanIndex(const QModelIndex &index) const
{
    const GridTableHeaderModel* tblModel = qobject_cast<GridTableHeaderModel*>(model());
    const int curRow = index.row();
    const int curCol = index.column();
    int i = curCol;
    while (i >= 0) {
        QModelIndex spanIndex = tblModel->index(curRow,i);
        QVariant span   = spanIndex.data(GridTableHeaderModel::ColumnSpanRole);
        if (span.isValid() && spanIndex.column()+span.toInt()-1 >= curCol)
            return spanIndex;
        i--;
    }
    return QModelIndex();
}

QModelIndex GridTableHeaderView::rowSpanIndex(const QModelIndex &index) const
{
    const GridTableHeaderModel* tblModel = qobject_cast<GridTableHeaderModel*>(model());
    const int curRow = index.row();
    const int curCol = index.column();
    int i = curRow;
    while (i >= 0) {
        QModelIndex spanIndex = tblModel->index(i,curCol);
        QVariant span   = spanIndex.data(GridTableHeaderModel::RowSpanRole);
        if (span.isValid() && spanIndex.row()+span.toInt()-1 >= curRow)
            return spanIndex;
        i--;
    }
    return QModelIndex();
}

int GridTableHeaderView::columnSpanSize(int row, int from, int spanCount) const
{
    const GridTableHeaderModel* tblModel = qobject_cast<GridTableHeaderModel*>(model());
    int span = 0;
    for (int i=from;i<from+spanCount;++i){
        QSize cellSize = tblModel->index(row,i).data(Qt::SizeHintRole).toSize();
        span += cellSize.width();
    }
    return span;
}

int GridTableHeaderView::rowSpanSize(int column, int from, int spanCount) const
{
    const GridTableHeaderModel* tblModel = qobject_cast<GridTableHeaderModel*>(model());
    int span = 0;
    for (int i=from;i<from+spanCount;++i){
        QSize cellSize = tblModel->index(i,column).data(Qt::SizeHintRole).toSize();
        span += cellSize.height();
    }
    return span;
}

int GridTableHeaderView::getSectionRange(QModelIndex &index, int *beginSection, int *endSection) const
{
    QModelIndex colSpanIdx = columnSpanIndex(index);
    QModelIndex rowSpanIdx = rowSpanIndex(index);

    if (colSpanIdx.isValid()){
        int colSpanFrom = colSpanIdx.column();
        int colSpanCnt  = colSpanIdx.data(GridTableHeaderModel::ColumnSpanRole).toInt();

        int colSpanTo   = colSpanFrom+colSpanCnt-1;
        if (orientation() == Qt::Horizontal) {
            *beginSection = colSpanFrom;
            *endSection   = colSpanTo;
            index = colSpanIdx;
            return colSpanCnt;
        }
        else{
            QVariant subRowSpanData = colSpanIdx.data(GridTableHeaderModel::RowSpanRole);
            if (subRowSpanData.isValid())
            {
                int subRowSpanFrom = colSpanIdx.row();
                int subRowSpanCnt  = subRowSpanData.toInt();
                int subRowSpanTo   = subRowSpanFrom+subRowSpanCnt-1;
                *beginSection = subRowSpanFrom;
                *endSection   = subRowSpanTo;
                index = colSpanIdx;
                return subRowSpanCnt;
            }
        }
    }

    if (rowSpanIdx.isValid())
    {
        int rowSpanFrom = rowSpanIdx.row();
        int rowSpanCnt  = rowSpanIdx.data(GridTableHeaderModel::RowSpanRole).toInt();
        int rowSpanTo   = rowSpanFrom+rowSpanCnt-1;
        if (orientation() == Qt::Vertical) {
            *beginSection = rowSpanFrom;
            *endSection   = rowSpanTo;
            index = rowSpanIdx;
            return rowSpanCnt;
        }
        else {
            QVariant subColSpanData = rowSpanIdx.data(GridTableHeaderModel::ColumnSpanRole);
            if (subColSpanData.isValid())
            {
                int subColSpanFrom = rowSpanIdx.column();
                int subColSpanCnt  = subColSpanData.toInt();
                int subColSpanTo   = subColSpanFrom+subColSpanCnt-1;
                *beginSection = subColSpanFrom;
                *endSection   = subColSpanTo;
                index = rowSpanIdx;
                return subColSpanCnt;
            }
        }
    }

    return 0;
}

void GridTableHeaderView::mousePressEvent(QMouseEvent *event)
{
    QHeaderView::mousePressEvent(event);
    QModelIndex index = indexAt(event->pos());

    if (index.isValid()){
        int beginSection = (orientation() == Qt::Horizontal) ? index.column() : index.row();;
        int endSection = beginSection;
        if (getSectionRange(index,&beginSection,&endSection) > 0)
            emit sectionPressed(beginSection,endSection);
        else
            emit sectionPressed(beginSection,endSection);
    }
}

void GridTableHeaderView::onSectionResized(int logicalIndex, int oldSize, int newSize)
{
    Q_UNUSED(oldSize)
    GridTableHeaderModel* tblModel = qobject_cast<GridTableHeaderModel*>(this->model());

    const int level = (orientation() == Qt::Horizontal)?tblModel->rowCount():tblModel->columnCount();
    int pos = sectionViewportPosition(logicalIndex);
    int xx  = (orientation() == Qt::Horizontal) ? pos : 0;
    int yy  = (orientation() == Qt::Horizontal)?0:pos;
    QRect sectionRect(xx,yy,0,0);
    for (int i=0; i < level; ++i) {
        QModelIndex cellIndex = (orientation() == Qt::Horizontal)?tblModel->index(i,logicalIndex):tblModel->index(logicalIndex,i);
        QSize cellSize=cellIndex.data(Qt::SizeHintRole).toSize();
        // set position of cell
        if (orientation() == Qt::Horizontal) {
            sectionRect.setTop(rowSpanSize(logicalIndex,0,i));
            cellSize.setWidth(newSize);
        }
        else {
            sectionRect.setLeft(columnSpanSize(logicalIndex,0,i));
            cellSize.setHeight(newSize);
        }
        tblModel->setData(cellIndex,cellSize,Qt::SizeHintRole);

        QModelIndex colSpanIdx = columnSpanIndex(cellIndex);
        QModelIndex rowSpanIdx = rowSpanIndex(cellIndex);

        if (colSpanIdx.isValid()){
            int colSpanFrom = colSpanIdx.column();
            if (orientation() == Qt::Horizontal)
                sectionRect.setLeft(sectionViewportPosition(colSpanFrom));
            else {
                sectionRect.setLeft(columnSpanSize(logicalIndex,0,colSpanFrom));
            }

        }
        if (rowSpanIdx.isValid()){
            int rowSpanFrom = rowSpanIdx.row();
            if (orientation() == Qt::Vertical)
                sectionRect.setTop(sectionViewportPosition(rowSpanFrom));
            else
                sectionRect.setTop(rowSpanSize(logicalIndex,0,rowSpanFrom));
        }
        QRect rToUpdate(sectionRect);
        rToUpdate.setWidth(viewport()->width()-sectionRect.left());
        rToUpdate.setHeight(viewport()->height()-sectionRect.top());
        viewport()->update(rToUpdate.normalized());
    }
}
