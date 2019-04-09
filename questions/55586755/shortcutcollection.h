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
    void appendItem(ShortcutItem*);
    int itemsCount() const;
    ShortcutItem *item(int) const;
    void clearItems();
private:
    static void appendItem(QQmlListProperty<ShortcutItem>*, ShortcutItem*);
    static int itemsCount(QQmlListProperty<ShortcutItem>*);
    static ShortcutItem* item(QQmlListProperty<ShortcutItem>*, int);
    static void clearItems(QQmlListProperty<ShortcutItem>*);
    QVector<ShortcutItem*> m_items;
};

#endif // SHORTCUTCOLLECTION_H
