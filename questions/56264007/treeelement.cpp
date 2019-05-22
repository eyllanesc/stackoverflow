#include "treeelement.h"

TreeElement::TreeElement(QObject *parent) :
    QObject(parent),
    m_parent(nullptr) {}

TreeElement *TreeElement::parentItem() const{
    return m_parent;
}


QQmlListProperty<TreeElement> TreeElement::items(){
    return  QQmlListProperty<TreeElement> (this,
                                           this,
                                           &TreeElement::appendElement,
                                           &TreeElement::countElement,
                                           &TreeElement::atElement,
                                           &TreeElement::clearElement);
}

TreeElement *TreeElement::child(int index) const{
    if(index < 0 || index >= m_childs.length())
        return nullptr;
    return m_childs.at(index);
}

void TreeElement::clear(){
    qDeleteAll(m_childs);
    m_childs.clear();
}

bool TreeElement::insertItem(TreeElement *item, int pos){
    if(pos > m_childs.count())
        return false;
    if(pos < 0)
        pos = m_childs.count();
    item->m_parent = this;
    item->setParent(this);
    m_childs.insert(pos, item);
    return true;
}

int TreeElement::pos() const{
    TreeElement *parent = parentItem();
    if(parent)
        return parent->m_childs.indexOf(const_cast<TreeElement *>(this));
    return 0;
}

int TreeElement::count() const{
    return m_childs.size();
}

void TreeElement::appendElement(QQmlListProperty<TreeElement> *property, TreeElement *value){
    TreeElement *parent = qobject_cast<TreeElement *>(property->object);
    parent->insertItem(value);
}

int TreeElement::countElement(QQmlListProperty<TreeElement> *property){
    TreeElement *parent = qobject_cast<TreeElement *>(property->object);
    return parent->count();
}

void TreeElement::clearElement(QQmlListProperty<TreeElement> *property){
    TreeElement *parent = qobject_cast<TreeElement *>(property->object);
    parent->clear();
}

TreeElement *TreeElement::atElement(QQmlListProperty<TreeElement> *property, int index){
    TreeElement *parent = qobject_cast<TreeElement *>(property->object);
    if(index < 0 || index >= parent->count())
        return nullptr;
    return parent->child(index);
}
