#include "mousememory.h"
#include <QDebug>

MouseMemory::MouseMemory(QObject *parent) : QObject(parent) {}

void MouseMemory::clear() { qDebug() << __PRETTY_FUNCTION__; }
