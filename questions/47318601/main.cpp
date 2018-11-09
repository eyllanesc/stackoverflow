#include "connection.h"
#include "insertdialog.h"

#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDriver>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlRecord>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection())
        return EXIT_FAILURE;


    QWidget w;
    QTableView view(&w);
    QPushButton btn("Insert", &w);

    QSqlTableModel model;
    model.setTable("person");
    model.select();
    view.setModel(&model);

    QVBoxLayout layout(&w);
    layout.addWidget(&view);
    layout.addWidget(&btn);
    w.show();

    QObject::connect(&btn, &QPushButton::clicked, [&model](){

        QSqlDatabase db = model.database();
        if(db.driver()->hasFeature(QSqlDriver::Transactions)){
            qDebug()<<"QSqlDriver::Transactions";
        }

        InsertDialog dial;
        if(dial.exec()== InsertDialog::Accepted){
            db.transaction();
            QString f = dial.firstname();
            QString l = dial.lastname();

            QSqlRecord record = model.record();
            /* since the id field has the autoincrement attribute,
             * it is not necessary to indicate its value,
             * that is why this field of the request is removed.
            */
            record.remove(record.indexOf("id"));//
            record.setValue("firstname", f);
            record.setValue("lastname", l);
            /*-1 is set to indicate that it will be added to the last row*/
            if(model.insertRecord(-1, record)){
                qDebug()<<"successful insertion";
            }
            else{
                db.rollback();
            }
        }
    });

    return a.exec();
}
