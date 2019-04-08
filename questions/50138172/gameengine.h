#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "gameboard.hh"

#include <QObject>
#include <memory>
#include <random>

class GameEngine : public QObject {
  Q_OBJECT
public:
  explicit GameEngine(GameBoard &gameBoard, int seed = 0,
                      QObject *parent = nullptr);
  void initialize();
  void launchSplash(const QPointF &p);

private:
  // The data model of the game board.
  std::vector<std::vector<std::shared_ptr<Bubble>>> board_;

  // Access to the graphical presentation of the game board.
  GameBoard &graphicalGameBoard_;

  // The amount of water that can be used during the game.
  int waterTank_;

  // Random number generator for initializing the board.
  std::default_random_engine randomEngine_;
  std::shared_ptr<Bubble> bubbleAt(int x, int y) const;
  SplashItem splash_item;
};

#endif // GAMEENGINE_H
