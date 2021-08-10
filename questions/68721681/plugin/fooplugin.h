#ifndef FOOPLUGIN_H
#define FOOPLUGIN_H

#include "foointerface.h"

#include <QObject>
#include <QtPlugin>


class FooPlugin : public QObject, FooInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Examples.FooInterface" FILE "fooplugin.json")
    Q_INTERFACES(FooInterface)
public:
    QString print();
};

#endif // FOOPLUGIN_H
