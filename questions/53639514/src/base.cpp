#include "base.h"

Base::Base(QObject *parent) : QObject(parent) {}

QString Base::doStuff() { return "Base"; }
