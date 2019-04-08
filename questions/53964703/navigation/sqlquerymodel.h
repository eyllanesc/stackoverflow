#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

class SqlQueryModel : public QSqlQueryModel {
  Q_OBJECT
  Q_PROPERTY(
      QString query READ queryStr WRITE setQueryStr NOTIFY queryStrChanged)
  Q_PROPERTY(QStringList userRoleNames READ userRoleNames CONSTANT)
public:
  using QSqlQueryModel::QSqlQueryModel;
  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    for (int i = 0; i < record().count(); i++) {
      roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
    return roles;
  }
  QVariant data(const QModelIndex &index, int role) const {
    QVariant value;
    if (index.isValid()) {
      if (role < Qt::UserRole) {
        value = QSqlQueryModel::data(index, role);
      } else {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
      }
    }
    return value;
  }
  QString queryStr() const { return query().lastQuery(); }
  void setQueryStr(const QString &query) {
    if (queryStr() == query)
      return;
    setQuery(query);
    emit queryStrChanged();
  }
  QStringList userRoleNames() const {
    QStringList names;
    for (int i = 0; i < record().count(); i++) {
      names << record().fieldName(i).toUtf8();
    }
    return names;
  }
signals:
  void queryStrChanged();
};
#endif // SQLQUERYMODEL_H
