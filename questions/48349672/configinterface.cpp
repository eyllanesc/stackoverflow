#include "configinterface.h"

ConfigInterface::ConfigInterface(QObject *parent) : QObject(parent) {}

ConfigInterface::~ConfigInterface() {}

QString ConfigInterface::getDescription() const { return _description; }

void ConfigInterface::setDescription(const QString &description) {
  if (_description == description)
    return;
  emit descriptionChanged(description);
  _description = description;
}

QString ConfigInterface::getTag() const { return _tag; }

void ConfigInterface::setTag(const QString &tag) {
  if (tag == _tag)
    return;
  emit tagChanged(tag);
  _tag = tag;
}
