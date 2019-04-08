#include "stopmainwindow.h"
#include "ui_stopmainwindow.h"

#include <QDebug>
#include <QLabel>
#include <QMediaPlaylist>
#include <QPushButton>

StopMainWindow::StopMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::StopMainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_Start, &QPushButton::clicked, this,
          &StopMainWindow::start);
  connect(ui->pushButton_go_on, &QPushButton::clicked, this,
          &StopMainWindow::pause);
  connect(ui->pushButton_Stop, &QPushButton::clicked, this,
          &StopMainWindow::stop);

  ui->pushButton_Start->setEnabled(true);
  ui->pushButton_go_on->setEnabled(false);
  ui->pushButton_Stop->setEnabled(false);

  music = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
  QMediaPlaylist *playlist = new QMediaPlaylist;
  playlist->addMedia(QUrl("qrc:/sounds/tik.mp3"));
  playlist->setPlaybackMode(QMediaPlaylist::Loop);

  music->setPlaylist(playlist);
  music->setVolume(100);

  mRunning = false;
}

StopMainWindow::~StopMainWindow() { delete ui; }

void StopMainWindow::start() {
  ui->pushButton_Start->setEnabled(false);
  ui->pushButton_go_on->setEnabled(true);
  ui->pushButton_Stop->setEnabled(true);
  music->play();

  mRunning = true;

  mStartTime = QDateTime::currentDateTime();

  startTimer(1);
}

void StopMainWindow::pause() {
  music->pause();
  mRunning = false;
  ui->pushButton_Start->setEnabled(true);
  ui->pushButton_go_on->setEnabled(false);
  ui->pushButton_Stop->setEnabled(true);
  mTotalTime += mSessionTime;
}

void StopMainWindow::stop() {
  ui->pushButton_Start->setEnabled(true);
  ui->pushButton_go_on->setEnabled(false);
  ui->pushButton_Stop->setEnabled(false);

  music->stop();
  mRunning = false;
}

void StopMainWindow::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event)
  if (mRunning) {
    mSessionTime = mStartTime.msecsTo(QDateTime::currentDateTime());
    qint64 time = mTotalTime + mSessionTime;
    time *= 111;

    unsigned int h = time / 1000 / 60 / 60;
    unsigned int m = (time / 1000 / 60) - (h * 60);
    unsigned int s = (time / 1000) - ((m + (h * 60)) * 60);
    unsigned int ms = time - (s + ((m + (h * 60)) * 60)) * 1000;

    const QString diff = QString("%1:%2:%3,%4")
                             .arg(h, 2, 10, QChar('0'))
                             .arg(m, 2, 10, QChar('0'))
                             .arg(s, 2, 10, QChar('0'))
                             .arg(ms, 3, 10, QChar('0'));
    ui->mLabel->setText(diff);
  }
}
