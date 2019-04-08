#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>

class Player : public QLabel {
  enum { IDLE_LEFT, IDLE_RIGHT, RUN_LEFT, RUN_RIGHT };

public:
  Player(qreal playerSize, QSize sceneSize, QWidget *parent = Q_NULLPTR);

protected:
  void keyPressEvent(QKeyEvent *event);

private:
  void setCurrentAnimation(int animationCode);
  int curr_Animation_Code;
};

#endif // PLAYER_H
