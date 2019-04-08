#ifndef SQLTRAFFICMODEL_H
#define SQLTRAFFICMODEL_H

#include <QSqlQuery>
#include <QSqlQueryModel>

class SqlTrafficModel : public QSqlQueryModel {
  Q_OBJECT
  Q_PROPERTY(
      QString queryStr READ queryStr WRITE setQueryStr NOTIFY queryStrChanged)
public:
  SqlTrafficModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {}
  Q_INVOKABLE QStringList getColumn(int col) {
    QStringList mColumn;
    for (int row = 0; row < rowCount(); ++row) {
      mColumn << index(row, col).data().toString();
    }
    return mColumn;
  }

  QString queryStr() const { return mQueryStr; }
  void setQueryStr(const QString &queryStr) {
    if (queryStr == mQueryStr)
      return;
    mQueryStr = queryStr;
    setQuery(mQueryStr);
    emit queryStrChanged();
  }

signals:
  void queryStrChanged();

private:
  QString mQueryStr;
};

#endif // SQLTRAFFICMODEL_H
