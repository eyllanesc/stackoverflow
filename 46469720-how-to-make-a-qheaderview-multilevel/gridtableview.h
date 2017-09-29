#ifndef GRIDTABLEVIEW_H
#define GRIDTABLEVIEW_H

#include <QTableView>

class QStandardItemModel;
class GridTableHeaderView;

class GridTableView : public QTableView
{
    Q_OBJECT
public:
    explicit GridTableView(QWidget *parent = nullptr);
    void setGridHeaderview(Qt::Orientation orientation, int levels);
    GridTableHeaderView *gridHeaderview(Qt::Orientation orientation);

private slots:
    void horizontalHeaderSectionPressed(int beginSection, int endSection);
    void verticalHeaderSectionPressed(int beginSection, int endSection);
};

#endif // GRIDTABLEVIEW_H
