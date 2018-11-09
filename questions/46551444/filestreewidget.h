#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QDropEvent>
#include <QTreeWidget>
#include <QMimeData>
#include <QFileInfo>

#include <QDebug>

class FilesTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    FilesTreeWidget(QWidget *parent= Q_NULLPTR):
        QTreeWidget(parent)
    {
        setAcceptDrops(true);
        setDropIndicatorShown(true);
        setColumnCount(2);
    }

protected:
    bool dropMimeData(QTreeWidgetItem *parent, int /*index*/, const QMimeData *data, Qt::DropAction /*action*/)
    {

        for(const QUrl url: data->urls()) {
            const QFileInfo info( url.toLocalFile());
            if(info.isFile()){
                QTreeWidgetItem *item;
                if (parent){
                    item = new QTreeWidgetItem(parent);
                    parent->setExpanded(true);
                }
                else
                    item = new QTreeWidgetItem(this);
                item->setText(0, info.fileName());
                item->setText(1, info.filePath());
            }
        }
        return true;
    }

    QStringList mimeTypes () const
    {
        return QStringList()<<"text/uri-list";
    }

    Qt::DropActions supportedDropActions () const
    {
        return Qt::CopyAction;
    }

};

#endif // TREEWIDGET_H
