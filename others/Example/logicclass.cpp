#include "logicclass.h"
#include <QDebug>

LogicClass::LogicClass(QObject *parent) : QObject(parent) {}

void LogicClass::on_click_slot() { qDebug() << "clicked"; }
