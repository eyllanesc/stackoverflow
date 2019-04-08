#include "derived.h"

Derived::Derived(QObject *parent) : Base(parent) {}

QString Derived::doStuff() { return "Derived"; }
