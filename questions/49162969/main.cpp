#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

class NotifyLabel : public QLabel {
  Q_OBJECT
  QTimer timer{this};
  QPropertyAnimation slideIn{this, "pos"};

public:
  NotifyLabel() {
    timer.setSingleShot(true);
    timer.setInterval(3000);
    connect(&timer, &QTimer::timeout, this, &NotifyLabel::hide);
    slideIn.setDuration(750);
    slideIn.setStartValue(QPoint(1800, 30));
    slideIn.setEndValue(QPoint(1250, 30));
    slideIn.setEasingCurve(QEasingCurve::InBack);
  }
  void displayNotif(int value) {
    if (timer.isActive()) {
      timer.stop();
    } else
      slideIn.start();
    setText(QString("%1% volume").arg(value));
    show();
    timer.start();
  }
};

static int getVolume() {
  // emulate volume
  return 1 + rand() % 3;
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  NotifyLabel w;
  QTimer timer;

  int current_vol;

  QObject::connect(&timer, &QTimer::timeout, [&w, &current_vol]() {
    int update_vol = getVolume();

    qDebug() << update_vol;

    if (current_vol != update_vol) {
      w.displayNotif(update_vol);
    }
    current_vol = update_vol;
  });
  timer.start(2000);
  return a.exec();
}

#include "main.moc"
