#include "mapwidget.h"
#include "coordinatemodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    MapWidget w;
    w.model()->append(QGeoCoordinate(45.782074, -6.871263));
    w.model()->append(QGeoCoordinate(50.782074, -1.871263));
    w.model()->append(QGeoCoordinate(55.782074, 4.871263));
    w.model()->append(QGeoCoordinate(45.782074, 4.871263));
    w.model()->append(QGeoCoordinate(50.782074, 4.871263));
    w.model()->append(QGeoCoordinate(55.782074, 4.871263));
    w.show();
    return app.exec();
}
