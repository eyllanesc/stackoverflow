#include "gameboard.hh"
#include "gameengine.h"
#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  GameBoard graphicalGameBoard;
  GameEngine engine(graphicalGameBoard);
  MainWindow w(graphicalGameBoard);
  QObject::connect(&graphicalGameBoard, &GameBoard::mouseClick, &engine,
                   &GameEngine::launchSplash);
  w.show();

  return a.exec();
}
