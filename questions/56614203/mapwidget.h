#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QQuickWidget>

class CoordinateModel;

class MapWidget : public QQuickWidget
{
public:
    MapWidget(QWidget *parent=nullptr);
    CoordinateModel *model() const;
private:
    CoordinateModel *m_model;
};

#endif // MAPWIDGET_H
