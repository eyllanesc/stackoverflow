#ifndef PYTHONUTILS_H
#define PYTHONUTILS_H

class QString;

namespace PythonUtils {
enum State
{
    PythonUninitialized,
    PythonInitialized,
    AppModuleLoaded
};
bool loadPlugins(const QString &modulePath, const QString &moduleName, const QString &function);
State init();
}

#endif // PYTHONUTILS_H
