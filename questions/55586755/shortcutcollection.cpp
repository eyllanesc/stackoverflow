#include "shortcutcollection.h"

ShortcutCollection::ShortcutCollection(QObject *parent):
    QObject(parent)
{
}

QQmlListProperty<ShortcutItem> ShortcutCollection::items()
{
    return QQmlListProperty<ShortcutItem>(this, m_items);
}

int ShortcutCollection::itemsCount() const
{
    return m_items.count();
}

ShortcutItem *ShortcutCollection::item(int index) const
{
    return m_items.at(index);
}

