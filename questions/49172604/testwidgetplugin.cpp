#include "testwidgetplugin.h"
#include "testwidget.h"

#include <QtPlugin>

TestWidgetPlugin::TestWidgetPlugin(QObject *parent) : QObject(parent) {
  m_initialized = false;
}

void TestWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool TestWidgetPlugin::isInitialized() const { return m_initialized; }

QWidget *TestWidgetPlugin::createWidget(QWidget *parent) {
  return new TestWidget(parent);
}

QString TestWidgetPlugin::name() const { return QLatin1String("TestWidget"); }

QString TestWidgetPlugin::group() const {
  return QLatin1String("TestWidgetGroup");
}

QIcon TestWidgetPlugin::icon() const {
  return QIcon(QLatin1String(":/if_Sharethis_322291.png"));
}

QString TestWidgetPlugin::toolTip() const {
  return QLatin1String("I am TestWidget");
}

QString TestWidgetPlugin::whatsThis() const { return QLatin1String(""); }

bool TestWidgetPlugin::isContainer() const { return false; }

QString TestWidgetPlugin::domXml() const {
  return QLatin1String(
      "<widget class=\"TestWidget\" name=\"testWidget\">\n</widget>\n");
}

QString TestWidgetPlugin::includeFile() const {
  return QLatin1String("testwidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(testwidgetplugin, TestWidgetPlugin)
#endif // QT_VERSION < 0x050000
