#include "glineeditdialog.h"
#include "glineeditmenufactory.h"

#include <glineedit.h>

#include <QtDesigner/QDesignerFormEditorInterface>
#include <QAction>

//#include <qhsidebardialog.h>

GLineEditTaskmenu::GLineEditTaskmenu(GLineEdit *glineedit,  QObject *parent):
    QObject(parent),
    editItemsAction(new QAction(tr("Edit Actions..."), this)),
    mGLineEdit(glineedit)
{
    connect(editItemsAction, &QAction::triggered, this, &GLineEditTaskmenu::editItems);
}

QAction *GLineEditTaskmenu::preferredEditAction() const
{
    return editItemsAction;
}

QList<QAction *> GLineEditTaskmenu::taskActions() const
{
    QList<QAction *> list;
    list.append(editItemsAction);
    return list;
}

void GLineEditTaskmenu::editItems()
{
    GLineEditDialog dialog(mGLineEdit);
    dialog.exec();

}


GLineEditMenuFactory::GLineEditMenuFactory(QExtensionManager *parent):
    QExtensionFactory(parent)
{

}

QObject *GLineEditMenuFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
            return 0;

        if (GLineEdit *glineedit = qobject_cast<GLineEdit*>(object))
            return new GLineEditTaskmenu(glineedit, parent);

        return 0;
}
