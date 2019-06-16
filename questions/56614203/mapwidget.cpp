#include "coordinatemodel.h"
#include "mapwidget.h"

#include <QQmlContext>

MapWidget::MapWidget(QWidget *parent):
    QQuickWidget(parent),
    m_model(new CoordinateModel{this})
{
    rootContext()->setContextProperty("myModel", m_model);
    setSource(QUrl(QStringLiteral("qrc:/main.qml")));
}

CoordinateModel *MapWidget::model() const
{
    return m_model;
}
