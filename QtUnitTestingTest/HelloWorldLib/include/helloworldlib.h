#ifndef HELLOWORLDLIB_H
#define HELLOWORLDLIB_H

#include "helloworldlib_global.h"

#include <QDebug>

class HELLOWORLDLIBSHARED_EXPORT HelloWorldLib: public QObject
{
    Q_OBJECT

public:
    HelloWorldLib(){

    }
    static bool returnTrue()
    {
        return true;
    }

public slots:
    void someSlot()
    {
        qDebug() << "test";
    }

};

#endif // HELLOWORLDLIB_H
