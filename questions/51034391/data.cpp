#include "data.h"
#include <iostream>

Data::Data(QObject *parent) : QObject(parent) {
  std::cout << "constructed" << std::endl;
  menu.append({QStringLiteral("A"), QStringLiteral("1"), QStringLiteral("null"),
               QVariantList()});
}

QVector<unit> Data::items() const { return menu; }

bool Data::setItemAt(int index, const unit &item) {
  if (index < 0 || index >= menu.size())
    return false;

  const unit &oldItem = menu.at(index);

  if (item == oldItem)
    return false;

  menu[index] = item;
  return true;
}

void Data::appendItem(const QString name, const QString &parent,
                      const QString &level, const QVariantList &v) {

  emit preItemAppended();
  unit item{name, parent, level, v};
  menu.append(item);
  emit postItemAppended();
}

void Data::removeItem(const QString props) {
  for (int i = 0; i < menu.size();) {
    if (menu.at(i).name == props) {
      emit preItemRemoved(i);
      menu.removeAt(i);
      emit postItemRemoved();
      return;
    } else {
      ++i;
    }
  }
}
