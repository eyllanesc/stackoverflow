#include "testclassplugin.h"
#include "testclass.h"

#include <QtPlugin>

TestClassPlugin::TestClassPlugin(QObject *parent) : QObject(parent) {
  m_initialized = false;
}

void TestClassPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool TestClassPlugin::isInitialized() const { return m_initialized; }

QWidget *TestClassPlugin::createWidget(QWidget *parent) {
  return new TestClass(parent);
}

QString TestClassPlugin::name() const { return QLatin1String("TestClass"); }

QString TestClassPlugin::group() const { return QLatin1String(""); }

QIcon TestClassPlugin::icon() const { return QIcon(); }

QString TestClassPlugin::toolTip() const { return QLatin1String(""); }

QString TestClassPlugin::whatsThis() const { return QLatin1String(""); }

bool TestClassPlugin::isContainer() const { return false; }

QString TestClassPlugin::domXml() const {
  return QLatin1String(
      "<widget class=\"TestClass\" name=\"testClass\">\n</widget>\n");
}

QString TestClassPlugin::includeFile() const {
  return QLatin1String("testclass.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(testclassplugin, TestClassPlugin)
#endif // QT_VERSION < 0x050000
