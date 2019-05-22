#ifndef TreeElement_H
#define TreeElement_H

#include <QObject>
#include <QQmlListProperty>

class TreeElement : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QQmlListProperty<TreeElement> items READ items)
    Q_CLASSINFO("DefaultProperty", "items")
    TreeElement(QObject *parent = Q_NULLPTR);

    Q_INVOKABLE TreeElement *parentItem() const;
    bool insertItem(TreeElement *item, int pos = -1);
    QQmlListProperty<TreeElement> items();

    TreeElement *child(int index) const;
    void clear();

    Q_INVOKABLE int pos() const;
    Q_INVOKABLE int count() const;

private:
    static void appendElement(QQmlListProperty<TreeElement> *property, TreeElement *value);
    static int countElement(QQmlListProperty<TreeElement> *property);
    static void clearElement(QQmlListProperty<TreeElement> *property);
    static TreeElement *atElement(QQmlListProperty<TreeElement> *property, int index);

    QList<TreeElement *> m_childs;
    TreeElement *m_parent;
};
#endif // TreeElement_H
