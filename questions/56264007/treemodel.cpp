#include "treemodel.h"
#include "treeelement.h"

TreeModel::TreeModel(QObject *parent) :
    QAbstractItemModel(parent){
    m_root = new TreeElement;
}
TreeModel::~TreeModel(){
    delete m_root;
}

QHash<int, QByteArray> TreeModel::roleNames() const{
    return m_roles;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();
    TreeElement *item = static_cast<TreeElement*>(index.internalPointer());
    QByteArray roleName = m_roles[role];
    QVariant name = item->property(roleName.data());
    return name;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const{
    if (!index.isValid())
        return nullptr;
    return QAbstractItemModel::flags(index);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    TreeElement *parentItem = elementFromIndex(parent);
    TreeElement *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const{
    if (!index.isValid())
        return QModelIndex();
    TreeElement *childItem = static_cast<TreeElement*>(index.internalPointer());
    TreeElement *parentItem = static_cast<TreeElement *>(childItem->parentItem());
    if (parentItem == m_root)
        return QModelIndex();
    return createIndex(parentItem->pos(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const{
    if (parent.column() > 0)
        return 0;
    TreeElement *parentItem = elementFromIndex(parent);
    return parentItem->count();
}

int TreeModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return 1;
}

QQmlListProperty<TreeElement> TreeModel::items(){
    return m_root->items();
}

QVariantList TreeModel::roles() const{
    QVariantList list;
    QHashIterator<int, QByteArray> i(m_roles);
    while (i.hasNext()) {
        i.next();
        list.append(i.value());
    }

    return list;
}

void TreeModel::setRoles(const QVariantList &roles){
    static int nextRole = Qt::UserRole + 1;
    for(QVariant role : roles) {
        m_roles.insert(nextRole, role.toByteArray());
        nextRole ++;
    }
    emit rolesChanged();
}

QModelIndex TreeModel::indexFromElement(TreeElement *item){
    QVector<int> positions;
    QModelIndex result;
    if(item) {
        do{
            int pos = item->pos();
            positions.append(pos);
            item = item->parentItem();
        } while(item != nullptr);

        for (int i = positions.size() - 2; i >= 0 ; i--)
            result = index(positions[i], 0, result);
    }
    return result;
}


bool TreeModel::insertElement(TreeElement *item, const QModelIndex &parent, int pos){
    TreeElement *parentElement = elementFromIndex(parent);
    if(pos >= parentElement->count())
        return false;
    if(pos < 0)
        pos = parentElement->count();
    beginInsertRows(parent, pos, pos);
    bool retValue = parentElement->insertItem(item, pos);
    endInsertRows();
    return retValue;
}

TreeElement *TreeModel::elementFromIndex(const QModelIndex &index) const{
    if(index.isValid())
        return static_cast<TreeElement *>(index.internalPointer());
    return m_root;
}
