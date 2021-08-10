#ifndef FOOINTERFACE_H
#define FOOINTERFACE_H

#include <QObject>

class FooInterface
{
public:
    virtual ~FooInterface() = default;
    virtual QString print() = 0;
};

QT_BEGIN_NAMESPACE

#define EchoInterface_iid "org.qt-project.Qt.Examples.FooInterface"
Q_DECLARE_INTERFACE(FooInterface, EchoInterface_iid)
QT_END_NAMESPACE

#endif // FOOINTERFACE_H
