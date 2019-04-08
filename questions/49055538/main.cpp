#include "player.h"

#include <QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QGraphicsView w;

  QGraphicsScene gameScene;
  w.setScene(&gameScene);
  gameScene.setSceneRect(0, 0, 640, 480);

  Player *player = new Player(80, QSize(gameScene.width(), gameScene.height()));
  gameScene.addWidget(player);
  player->setFocus();

  w.show();

  return a.exec();
}
