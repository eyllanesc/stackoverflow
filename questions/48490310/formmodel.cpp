#include "formmodel.h"

#include <QColor>

FormModel::FormModel(QObject *parent) : QAbstractListModel(parent) {
  for (int i = 0; i < 10; i++) {
    Form form;
    form.nameForm = QString("name %1").arg(i);
    for (int j = 0; j < 9; j++) {
      QColor color(qrand() % 256, qrand() % 256, qrand() % 256);
      Tile tile{QString("name %1 %2").arg(i).arg(j), color.name()};
      form.grid << QVariant::fromValue(tile);
    }
    dashboard << form;
  }
}

QHash<int, QByteArray> FormModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameForm] = "nameForm";
  roles[Grid] = "grid";
  return roles;
}

int FormModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return dashboard.count();
}

QVariant FormModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 && index.row() >= dashboard.count())
    return QVariant();
  Form dashTemp = dashboard[index.row()];
  if (role == NameForm)
    return dashTemp.nameForm;
  else if (role == Grid)
    return dashTemp.grid;
  return QVariant();
}
