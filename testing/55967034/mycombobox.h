#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include "completerdata.h"

#include <QComboBox>

class QTreeView;
class CompleterSourceModel;
class CompleterProxyModel;

class MyComboBox : public QComboBox
{
public:
    MyComboBox( QWidget *p_parent = nullptr );
    CompleterData createTestData();

private:
    QTreeView *m_view = nullptr;
    CompleterSourceModel *m_sourceModel = nullptr;
    CompleterProxyModel *m_proxyModel =nullptr;
};

#endif // MYCOMBOBOX_H
