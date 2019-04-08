#ifndef APPENDPROXYMODEL_H
#define APPENDPROXYMODEL_H

#include <QIdentityProxyModel>

class AppendProxyModel : public QIdentityProxyModel {
public:
  using QIdentityProxyModel::QIdentityProxyModel;
  QVariant data(const QModelIndex &index, int role) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QModelIndex index(int row, int column, const QModelIndex &parent) const;
  QStringList defaults() const;
  void setDefaults(const QStringList &defaults);

private:
  QStringList mDefaults;
};

#endif // APPENDPROXYMODEL_H
