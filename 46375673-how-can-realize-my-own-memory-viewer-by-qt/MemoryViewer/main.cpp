#include "memoryviewer.h"
#include <QApplication>
#include <QFile>

#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    w.setLayout(new QVBoxLayout);

    QPushButton btn("Load File", &w);
    MemoryViewer viewer(&w);

    viewer.setData(QByteArray("Hello World"));

    w.layout()->addWidget(&btn);
    w.layout()->addWidget(&viewer);
    QFile file;

    QObject::connect(&btn, &QPushButton::clicked, [&w, &viewer, &file](){
        QString fileName = QFileDialog::getOpenFileName(&w, "Open File",
                                                        QDir::homePath());
        if(!fileName.isEmpty()){
            file.setFileName(fileName);
            viewer.setData(file);
        }
    });

    w.show();

    return a.exec();
}
