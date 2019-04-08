#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include <interfaceplugin.h>

#include <QDebug>
#include <QSignalSpy>
#include <QTimer>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  Interface *interface;
  QDir dir(qApp->applicationDirPath());
  dir.cd("plugins");
  for (auto &filename : dir.entryList(QDir::Files)) {
    QPluginLoader loader(dir.absoluteFilePath(filename));
    auto *plugin = loader.instance();
    if (plugin) {
      interface = qobject_cast<Interface *>(plugin);
      break;
    }
  }
  if (!interface) {
    qDebug() << "Couldn't load interface!";
    return 0;
  }

  // Verify plugin emits its `name` with `QSignalSpy`.
  QSignalSpy spy(interface, &Interface::name);
  QTimer::singleShot(100, interface, &Interface::getName);
  spy.wait();
  if (spy.count() == 1) {
    auto name = spy.takeFirst().at(0).toString();
    qDebug() << "Plugin emitted name:" << name;
  } else {
    qDebug() << "Not emitted!";
  }
  return 0;

  // return a.exec();
}
