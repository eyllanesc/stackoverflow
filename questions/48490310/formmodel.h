#ifndef FORMMODEL_H
#define FORMMODEL_H

#include <QAbstractListModel>

struct Tile {
  Q_GADGET
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(QString color MEMBER color)
public:
  QString name;
  QString color;
  Tile(const QString &name = "", const QString &color = "") {
    this->name = name;
    this->color = color;
  }
};
Q_DECLARE_METATYPE(Tile)

struct Form {
  Q_GADGET
  Q_PROPERTY(QString nameForm MEMBER nameForm)
  Q_PROPERTY(QVariantList grid MEMBER grid)
public:
  Form() {}
  QString nameForm;
  QVariantList grid;
};
Q_DECLARE_METATYPE(Form)

class FormModel : public QAbstractListModel {
  enum dashBoardRoles { NameForm = Qt::UserRole + 1, Grid };

public:
  FormModel(QObject *parent = Q_NULLPTR);
  QHash<int, QByteArray> roleNames() const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
  QList<Form> dashboard;
};

#endif // FORMMODEL_H
