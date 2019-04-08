#include "counter.h"
#include <QDebug>
#include <QLineEdit>
#include <QtTest>
#include <cmath>
#include <iostream>

// add necessary includes here

class tst_Counter : public QObject {
  Q_OBJECT
public:
  tst_Counter();
  ~tst_Counter();

private slots:
  void initTestCD();
};

tst_Counter::tst_Counter() : QObject() {}
tst_Counter::~tst_Counter() {}

void tst_Counter::initTestCD() {
  QLineEdit editSec;
  QLineEdit editMin;
  Counter counter(&editSec, &editMin);
  const int epsilon = 50; // ms

  for (int i = 0; i <= 10; i++) {
    int randsec = rand() % 60;
    int randmin = rand() % 60;
    randsec = 3;
    randmin = 0; // To test the tester faster

    QString randsecString = QString::number(randsec);
    QString randminString = QString::number(randmin);

    editSec.setText(randsecString);
    editMin.setText(randminString);

    counter.set(); // those are to input, they work fine, I checked
    qDebug() << "Starting the Timer at " << (counter.count) / 10;

    auto start = std::chrono::system_clock::now();
    counter.start(); //{timer->start();}
    while (counter.count > 0) {
      QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);
    }
    auto end = std::chrono::system_clock::now();
    counter.stop();
    auto check_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    int checkInt = check_ms.count();
    int delta_s = randsec + randmin * 60;
    int delta = std::abs(checkInt - delta_s);
    QVERIFY(delta < epsilon);

    qDebug() << "Sec counted: " << counter.count / 10;
    qDebug() << "msec passed: " << checkInt;
  }
}

QTEST_MAIN(tst_Counter)

#include "tst_counter.moc"
