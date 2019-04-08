#include "mousememory.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QtQuickTest>

class Setup : public QObject {
  Q_OBJECT
public:
  using QObject::QObject;
public slots:

#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
  void applicationAvailable() {}
#endif
  void qmlEngineAvailable(QQmlEngine *engine) {
    mouse.reset(new MouseMemory);
    engine->rootContext()->setContextProperty("mouse", mouse.data());
  }
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
  void cleanupTestCase() {}
#endif
private:
  QScopedPointer<MouseMemory> mouse;
};
QUICK_TEST_MAIN_WITH_SETUP(example, Setup)

#include "main.moc"
