#include <QString>
#include <QtTest>

#include <helloworldlib.h>

#include <QDebug>

class HelloWorldTestTest : public QObject {
  Q_OBJECT

public:
  HelloWorldTestTest();

private Q_SLOTS:
  void testCase1_data();
  void testCase1();
};

HelloWorldTestTest::HelloWorldTestTest() {}

void HelloWorldTestTest::testCase1_data() {
  QTest::addColumn<QString>("data");
  QTest::newRow("0") << QString();
}

void HelloWorldTestTest::testCase1() {
  QFETCH(QString, data);
  QVERIFY2(true, "Failure");

  HelloWorldLib hw;
  QVERIFY(hw.returnTrue());
}

QTEST_APPLESS_MAIN(HelloWorldTestTest)

#include "tst_helloworldtesttest.moc"
