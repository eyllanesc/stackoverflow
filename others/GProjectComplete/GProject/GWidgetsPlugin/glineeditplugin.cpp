#include "glineeditplugin.h"
#include "glineeditmenufactory.h"

#include <glineedit.h>

#include <QDesignerFormEditorInterface>
#include <QExtensionManager>
#include <QtPlugin>

GLineEditPlugin::GLineEditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GLineEditPlugin::initialize(QDesignerFormEditorInterface * formEditor)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    QExtensionManager *manager = formEditor->extensionManager();
    Q_ASSERT(manager != 0);

    manager->registerExtensions(new GLineEditMenuFactory(manager),
                                Q_TYPEID(QDesignerTaskMenuExtension));

    m_initialized = true;
}

bool GLineEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GLineEditPlugin::createWidget(QWidget *parent)
{
    return new GLineEdit(parent);
}

QString GLineEditPlugin::name() const
{
    return QLatin1String("GLineEdit");
}

QString GLineEditPlugin::group() const
{
    return QLatin1String("Google-Styled Widgets");
}

QIcon GLineEditPlugin::icon() const
{
    return QIcon();
}

QString GLineEditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GLineEditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GLineEditPlugin::isContainer() const
{
    return false;
}

QString GLineEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"GLineEdit\" name=\"gLineEdit\">\n</widget>\n");
}

QString GLineEditPlugin::includeFile() const
{
    return QLatin1String("glineedit.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(GLineEditPlugin, GLineEditPlugin)
#endif // QT_VERSION < 0x050000
