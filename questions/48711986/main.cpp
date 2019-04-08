#include "plotter.h"

#include <QApplication>
#include <QDebug>
#include <QTimer>

class Manager : public QObject {
  Q_OBJECT
public:
  Manager(QObject *parent = 0) : QObject(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_Timeout()));
    timer->start(10);
    time = 0;
  }
signals:
  void newPoint(const QPointF &p);
public slots:
  void on_Timeout() {
    time += 0.1;
    QPointF point(time, 5 + 5 * qSin(time / 20) * qExp(-time / 1000));
    emit newPoint(point);
  }

private:
  float time;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  plotter w;
  w.resize(640, 480);
  Manager manager;
  QObject::connect(&manager, SIGNAL(newPoint(QPointF)), &w,
                   SLOT(add_point(QPointF)));
  w.show();
  return a.exec();
}

#include "main.moc"
