#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QDialog>
#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>

#include <QDebug>

class TableView: public QTableView{
    Q_OBJECT
    QPersistentModelIndex lastIndex;
    QDialog *popup;
    QLabel *popupLabel;

public:
    TableView(QWidget *parent = Q_NULLPTR):QTableView(parent){
        viewport()->installEventFilter(this);
        setMouseTracking(true);

        popup = new QDialog(this, Qt::Popup | Qt::ToolTip);

        QVBoxLayout *layout = new QVBoxLayout;
        popupLabel = new QLabel(popup);
        popupLabel->setWordWrap(true);
        layout->addWidget(popupLabel);
        popupLabel->setTextFormat(Qt::RichText);
        //popupLabel->setOpenExternalLinks(true);
        popup->setLayout(layout);
        popup->installEventFilter(this);
    }

    bool eventFilter(QObject *watched, QEvent *event){
        if(viewport() == watched){
            if(event->type() == QEvent::MouseMove){
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                QModelIndex index = lastIndex;
                index = indexAt(mouseEvent->pos());
                //if(index!=lastIndex){
                    if(index.isValid()){
                        showPopup(index);
                    }
                    else{
                        popup->hide();
                    }
                //}
                lastIndex = QPersistentModelIndex(index);
            }
        }
        else if(popup == watched){
            if(event->type() == QEvent::Leave){
                popup->hide();
            }
        }

        return QTableView::eventFilter(watched, event);
    }

    void showPopup (const QModelIndex &index) const {
        if(index.column() == 1){
            QRect r = visualRect(index);
            popup->move(viewport()->mapToGlobal(r.bottomRight()));
            popup->setFixedWidth(r.width());
            popupLabel->setText(index.data(Qt::DisplayRole).toString());
            popup->adjustSize();
            popup->show();
        }
        else {
            popup->hide();
        }
    }
};


#endif // TABLEVIEW_H
