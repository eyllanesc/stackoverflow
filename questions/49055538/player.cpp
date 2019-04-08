#include "player.h"

#include <QKeyEvent>
#include <QMovie>

Player::Player(qreal playerSize, QSize sceneSize, QWidget *parent)
    : QLabel(parent) {
  setAttribute(Qt::WA_TranslucentBackground);
  setGeometry((sceneSize.width() - playerSize) / 2,
              (sceneSize.height() - playerSize) / 2, playerSize, playerSize);

  setCurrentAnimation(IDLE_LEFT);
  movie()->setScaledSize(size());
  movie()->start();
}

void Player::setCurrentAnimation(int animationCode) {
  curr_Animation_Code = animationCode;
  switch (animationCode) {
  case IDLE_LEFT:
    setMovie(new QMovie(":/player/Laura/idle_left.gif"));
    break;
  case IDLE_RIGHT:
    setMovie(new QMovie(":/player/Laura/idle_right.gif"));
    break;
  case RUN_LEFT:
    setMovie(new QMovie(":/player/Laura/run_left.gif"));
    break;
  case RUN_RIGHT:
    setMovie(new QMovie(":/player/Laura/run_right.gif"));
    break;
  }
}

void Player::keyPressEvent(QKeyEvent *event) {

  if (event->key() == Qt::Key_Left) {
    move(pos() + QPoint(-10, 0));
    if (curr_Animation_Code != RUN_LEFT) {
      movie()->stop();
      setCurrentAnimation(RUN_LEFT);
      movie()->start();
    }
  } else if (event->key() == Qt::Key_Right) {
    move(pos() + QPoint(10, 0));
    if (curr_Animation_Code != RUN_RIGHT) {
      movie()->stop();
      setCurrentAnimation(RUN_RIGHT);
      movie()->start();
    }
  }
}
