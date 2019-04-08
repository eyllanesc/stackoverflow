#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractListModel>

class Data;
class MyModel
    : public QAbstractListModel // Type needs to be defined in upper letter
{
  Q_OBJECT
  Q_PROPERTY(Data *datas READ datas WRITE setDatas)

public:
  explicit MyModel(QObject *parent = nullptr);
  enum { NameRole = Qt::UserRole, LevelRole, ParentRole, SublevelRole };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;
  virtual QHash<int, QByteArray> roleNames() const override;

  Data *datas() const;
  void setDatas(Data *data);

private:
  Data *mDatas;
};

#endif // MyModel_H
