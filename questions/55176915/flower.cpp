#include "flower.h"
#include <QDebug>

Flower::Flower(QObject *parent) : QObject(parent) {}
void Flower::onClicked() { qDebug() << __PRETTY_FUNCTION__; }
