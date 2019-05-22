#ifndef TreeModel_H
#define TreeModel_H

#include <QAbstractItemModel>
#include <QQmlListProperty>

class TreeElement;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    Q_PROPERTY(QQmlListProperty<TreeElement> items READ items)
    Q_PROPERTY(QVariantList roles READ roles WRITE setRoles NOTIFY rolesChanged)
    Q_CLASSINFO("DefaultProperty", "items")

    TreeModel(QObject *parent = Q_NULLPTR);
    ~TreeModel() override;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QQmlListProperty<TreeElement> items();

    QVariantList roles() const;
    void setRoles(const QVariantList &roles);

    Q_INVOKABLE QModelIndex indexFromElement(TreeElement *item);
    Q_INVOKABLE bool insertElement(TreeElement *item, const QModelIndex &parent = QModelIndex(), int pos = -1);

    TreeElement *elementFromIndex(const QModelIndex &index) const;

private:
    TreeElement *m_root;
    QHash<int, QByteArray> m_roles;

signals:
    void rolesChanged();
};

#endif // TreeModel_H
