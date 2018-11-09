#include <QApplication>
#include <QLabel>
#include <QTableWidget>
#include <QDebug>

class CustomLabel: public QLabel{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *){
        emit clicked();
    }
signals:
    void clicked();
};

class TableWidget: public QTableWidget{
    Q_OBJECT
public:
    TableWidget(QWidget* parent=Q_NULLPTR):QTableWidget(parent){
        setRowCount(10);
        setColumnCount(10);
        for(int i=0; i<rowCount(); i++){
            for(int j=0; j<columnCount(); j++){
                auto lbl = new CustomLabel;
                setCellWidget(i, j, lbl);
                connect(lbl, &CustomLabel::clicked, this, &TableWidget::onClicked);
            }
        }
    }
private slots:
    void onClicked(){
        auto lbl = qobject_cast<CustomLabel *>(sender());
        if(lbl){
           auto ix = indexAt(lbl->pos());
           qDebug()<<"Table Cell: [" <<ix.row()<< ","  <<ix.column()<< "]";
        }
    }
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TableWidget w;
    w.show();

    return a.exec();
}
