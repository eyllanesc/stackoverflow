#include "horizontalscrollarea.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    w.setLayout(new QVBoxLayout);

    QPushButton btn("Add", &w);

    int nrows = 2;
    int ncols = 2;

    HorizontalScrollArea scroll(nrows, ncols);

    w.layout()->addWidget(&btn);
    w.layout()->addWidget(&scroll);

    QObject::connect(&btn, &QPushButton::clicked, [&scroll, &nrows](){
        int column = scroll.columnCount();
        for(int row=0; row < nrows; row++){
            QLabel *label = new QLabel(QString("label: %1 %2")
                                       .arg(row)
                                       .arg(column));
            label->setFrameShape(QFrame::Box);
            label->setAlignment(Qt::AlignCenter);
            QColor color(qrand() % 256, qrand() % 256, qrand() % 256);
            label->setStyleSheet(QString("QLabel { background-color : %1;}")
                                 .arg(color.name()));
            scroll.addWidget(label, row, column);
        }
    });
    w.show();
    return a.exec();
}
