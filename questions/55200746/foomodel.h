#ifndef FOOMODEL_H
#define FOOMODEL_H

#include <QAbstractListModel>
#include <QColor>
#include <QRect>

struct Foo {
  QString name;
  QRect rect;
  QColor color;
};

class FooModel : public QAbstractListModel {
  Q_OBJECT
public:
  using QAbstractListModel::QAbstractListModel;
  enum FooRoles { NameRole = Qt::UserRole + 1000, RectRole, ColorRole };
  void append(const Foo &foo) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << foo;
    endInsertRows();
  }
  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    return parent.isValid() ? 0 : m_data.size();
  }
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    if (!index.isValid())
      return QVariant();
    if (index.row() >= 0 && index.row() < rowCount()) {
      Foo foo = m_data.at(index.row());
      if (role == NameRole)
        return foo.name;
      else if (role == RectRole)
        return foo.rect;
      else if (role == ColorRole)
        return foo.color;
    }
    return QVariant();
  }
  QHash<int, QByteArray> roleNames() const override {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "namerole";
    roles[RectRole] = "rectrole";
    roles[ColorRole] = "colorrole";
    return roles;
  }

private:
  QVector<Foo> m_data;
};
#endif // FOOMODEL_H
