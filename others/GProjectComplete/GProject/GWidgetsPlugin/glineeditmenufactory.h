#ifndef GLINEEDITMENUFACTORY_H
#define GLINEEDITMENUFACTORY_H

#include <QDesignerTaskMenuExtension>
#include <QExtensionFactory>

#include <glineedit.h>

class GLineEditTaskmenu: public QObject, public QDesignerTaskMenuExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerTaskMenuExtension)
public:
    GLineEditTaskmenu(GLineEdit *glineedit,  QObject *parent);
    QAction *preferredEditAction() const Q_DECL_OVERRIDE;
    QList<QAction *> taskActions() const Q_DECL_OVERRIDE;
private slots:
    void editItems();

private:
    QAction *editItemsAction;
    GLineEdit *mGLineEdit;
};


class GLineEditMenuFactory: public QExtensionFactory
{
    Q_OBJECT
public:
    GLineEditMenuFactory(QExtensionManager *parent = 0);

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const Q_DECL_OVERRIDE;

};

#endif // GLINEEDITMENUFACTORY_H
