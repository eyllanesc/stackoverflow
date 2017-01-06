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

    QString data = "";

public slots:
    void someSlot()
    {
        data = "aa";
        qDebug() << "test";
        emit ok();
    }
signals:
    void ok();

};

#endif // HELLOWORLDLIB_H
