#include "listwidget.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

class ItemWidget: public QWidget{
public:
    ItemWidget(QString str, QWidget* parent=Q_NULLPTR):QWidget(parent){
        QVBoxLayout* layout = new QVBoxLayout;
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        QHBoxLayout* contentLayout = new QHBoxLayout;
        contentLayout->setSizeConstraint(QLayout::SetFixedSize);
        contentLayout->setSpacing(0);

        contentLayout->addSpacing(5);
        contentLayout->setContentsMargins(10, 20, 10, 20);

        QLabel* iconLbl = new QLabel;
        iconLbl->setPixmap(QPixmap(":/icon.png"));
        iconLbl->setMaximumWidth(20);
        contentLayout->addWidget(iconLbl, 0, Qt::AlignTop);

        contentLayout->addSpacing(14);

        QVBoxLayout* pageInfoLayout = new QVBoxLayout;
        pageInfoLayout->setContentsMargins(0, 0, 0, 0);
        pageInfoLayout->setSpacing(0);

        QLabel* pageNameLbl = new QLabel("First line of text"+str);
        pageInfoLayout->addWidget(pageNameLbl);

        pageInfoLayout->addSpacing(4);

        QLabel* pagePreviewLbl = new QLabel("Second line of text"+str);
        pageInfoLayout->addWidget(pagePreviewLbl);

        contentLayout->addLayout(pageInfoLayout);

        layout->addLayout(contentLayout);

        setLayout(layout);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    ListWidget *listWidget = new ListWidget;
    listWidget->setAcceptDrops(true);
    listWidget->setDragDropMode(QAbstractItemView::InternalMove);
    listWidget->setDragEnabled(true);
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    for ( int i = 0 ; i < 50 ; ++i )
    {
        ItemWidget* item = new ItemWidget(QString::number(i));
        QListWidgetItem* listItem = new QListWidgetItem;
        listItem->setSizeHint(item->sizeHint());
        listWidget->addItem(listItem);
        listWidget->setItemWidget(listItem, item);
    }
    listWidget->show();

    return a.exec();
}
