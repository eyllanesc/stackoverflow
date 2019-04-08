#include "testwidget.h"

TestWidget::TestWidget(QWidget *parent) : QWidget(parent) {}

TestWidget::EnumTest TestWidget::test() const { return mTest; }

void TestWidget::setTest(const EnumTest &test) { mTest = test; }
