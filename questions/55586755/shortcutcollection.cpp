#include "shortcutcollection.h"

ShortcutCollection::ShortcutCollection(QObject *parent):
    QObject(parent)
{
}

QQmlListProperty<ShortcutItem> ShortcutCollection::items()
{
    return QQmlListProperty<ShortcutItem>(this, this,
                                    &ShortcutCollection::appendItem,
                                    &ShortcutCollection::itemsCount,
                                    &ShortcutCollection::item,
                                    &ShortcutCollection::clearItems);
}

void ShortcutCollection::appendItem(ShortcutItem *shorcut)
{
    m_items.append(shorcut);
}

int ShortcutCollection::itemsCount() const
{
    return m_items.count();
}

ShortcutItem *ShortcutCollection::item(int index) const
{
    return m_items.at(index);
}

void ShortcutCollection::clearItems()
{
    m_items.clear();
}

void ShortcutCollection::appendItem(QQmlListProperty<ShortcutItem> *list, ShortcutItem *p)
{
    reinterpret_cast< ShortcutCollection* >(list->data)->appendItem(p);
}

int ShortcutCollection::itemsCount(QQmlListProperty<ShortcutItem> *list)
{
    return reinterpret_cast< ShortcutCollection* >(list->data)->itemsCount();
}

ShortcutItem *ShortcutCollection::item(QQmlListProperty<ShortcutItem> *list, int i)
{
    return reinterpret_cast< ShortcutCollection* >(list->data)->item(i);
}

void ShortcutCollection::clearItems(QQmlListProperty<ShortcutItem> *list)
{
    reinterpret_cast< ShortcutCollection* >(list->data)->clearItems();
}
