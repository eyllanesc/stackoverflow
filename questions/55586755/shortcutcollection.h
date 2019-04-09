#ifndef SHORTCUTCOLLECTION_H
#define SHORTCUTCOLLECTION_H

#include <QObject>
#include <QVector>
#include <QQmlListProperty>
#include "shortcutitem.h"

class ShortcutCollection: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<ShortcutItem> items READ items)
    Q_CLASSINFO("DefaultProperty", "items")
public:
    ShortcutCollection(QObject *parent=nullptr);
    QQmlListProperty<ShortcutItem> items();
    int itemsCount() const;
    ShortcutItem *item(int) const;
private:
    QList<ShortcutItem*> m_items;
};

#endif // SHORTCUTCOLLECTION_H
