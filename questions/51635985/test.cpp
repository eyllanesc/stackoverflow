#include "test.h"
#include <QDebug>

test::test(QObject *parent) : QObject(parent) {}

void test::testFunc() { qDebug() << "Hello from C++!"; }
