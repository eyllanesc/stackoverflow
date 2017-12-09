#include "graphicsscene.h"

#include <QApplication>
#include <QCheckBox>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget widget;
    QVBoxLayout lay(&widget);
    QCheckBox checkbox("Show Grid");
    QGraphicsView view;
    GraphicsScene scene;
    view.setScene(&scene);
    lay.addWidget(&checkbox);
    lay.addWidget(&view);

    QObject::connect(&checkbox, &QCheckBox::stateChanged, [&scene](int state){
        scene.setGridVisible(state != Qt::Unchecked);
    });
    scene.addRect(40, 40, 100, 100, QPen(Qt::red), QBrush(Qt::blue));
    widget.show();
    return app.exec();
}
