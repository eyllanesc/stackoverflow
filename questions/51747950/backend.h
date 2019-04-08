#ifndef BACKEND_H
#define BACKEND_H

#include "custom_class.h"
#include <QList>
#include <QObject>
#include <QVariant>
#include <iostream>
#include <typeinfo>

class Backend : public QObject {
  Q_OBJECT

public:
  using QObject::QObject;
  Q_INVOKABLE void sendItems(const QVariantList &list) {
    std::cout << "size " << list.size() << std::endl;
    list_.clear();
    for (const QVariant &variant : list) {
      if (variant.canConvert<CustomClass *>()) {
        CustomClass *custom = variant.value<CustomClass *>();
        list_.append(custom);
        std::cout << "converted " << custom->name().toStdString() << std::endl;
      }
    }
  }

private:
  QList<CustomClass *> list_;
};

#endif // BACKEND_H
