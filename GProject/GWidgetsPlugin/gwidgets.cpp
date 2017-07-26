#include "glineeditplugin.h"
#include "gwidgets.h"

GWidgets::GWidgets(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new GLineEditPlugin(this));

}

QList<QDesignerCustomWidgetInterface*> GWidgets::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(gwidgetsplugin, GWidgets)
#endif // QT_VERSION < 0x050000
