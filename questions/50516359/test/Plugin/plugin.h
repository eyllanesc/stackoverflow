#ifndef PLUGIN_H
#define PLUGIN_H

#include "plugin_global.h"
#include <interfaceplugin.h>

class PLUGINSHARED_EXPORT Plugin : public Interface {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "interface")
  Q_INTERFACES(Interface)

public:
  // Override abstract function to emit the `name` signal
  void getName() override { emit name("plugin"); }
};

#endif // PLUGIN_H
