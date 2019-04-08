#ifndef PLUGIN_GLOBAL_H
#define PLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLUGIN_LIBRARY)
#define PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#define PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLUGIN_GLOBAL_H
