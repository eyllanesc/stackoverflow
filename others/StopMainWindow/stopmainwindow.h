#ifndef STOPMAINWINDOW_H
#define STOPMAINWINDOW_H

#include <QDateTime>
#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class StopMainWindow;
}

class StopMainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit StopMainWindow(QWidget *parent = 0);
  ~StopMainWindow();

private slots:
  void start();
  void pause();
  void stop();

protected:
  void timerEvent(QTimerEvent *event);

private:
  Ui::StopMainWindow *ui;
  QMediaPlayer *music;

  bool mRunning;
  QDateTime mStartTime;
  qint64 mSessionTime;
  qint64 mTotalTime;
};

#endif // STOPMAINWINDOW_H
