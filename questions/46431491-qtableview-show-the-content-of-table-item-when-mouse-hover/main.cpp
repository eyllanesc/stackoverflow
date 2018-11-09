#include "tableview.h"

#include <QApplication>
#include <QStandardItemModel>


const QString text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry."
                     "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s,"
                     " when an unknown printer took a galley of type and scrambled it to make a type specimen book."
                     "It has survived not only five centuries, but also the leap into electronic typesetting,"
                     " remaining essentially unchanged."
                     "It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages,"
                     "and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TableView w;

    QStandardItemModel model(10,2);

    for(int row = 0; row < model.rowCount(); row++)
    {
        for(int col = 0; col < model.columnCount(); col++)
        {
            QModelIndex index = model.index(row,col,QModelIndex());
            if(col==1)
                model.setData(index, text);
            else
                model.setData(index,QString("%1, %2").arg(row).arg(col));
        }
    }

    w.setModel(&model);

    w.show();

    return a.exec();
}
