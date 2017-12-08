#include "interfacageqml.h"
#include <QDebug>

interfacageQML* interfacageQML::instance = 0;

interfacageQML *interfacageQML::getInstance()
{
    if (instance == 0)
        instance = new interfacageQML;
    return instance;
}

interfacageQML::interfacageQML(QObject *parent) : QObject(parent)
{
}

interfacageQML::~interfacageQML()
{
}

void interfacageQML::mouseClick()
{
    qDebug() << "qmlinterface::mouseClick()";
    emit clicked();
}
