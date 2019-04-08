#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // scene
  scene = new QGraphicsScene(0, 0, 1050, 600);
  // player
  player =
      new QGraphicsPixmapItem(QPixmap(":/img/whitedog.png").scaled(100, 100));
  player->setPos(350, 500);
  scene->addItem(player);
  // view
  view = new QGraphicsView;
  view->setScene(scene);
  view->installEventFilter(this);
  setCentralWidget(view);
  view->setFixedSize(1055, 605);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  if (watched == view && event->type() == QEvent::KeyPress) {
    QKeyEvent *kevent = static_cast<QKeyEvent *>(event);
    if (kevent->key() == Qt::Key_Down) {
      player->setPos(player->pos() + QPointF(0, 10));
      return true;
    }
    if (kevent->key() == Qt::Key_Up) {
      player->setPos(player->pos() - QPointF(0, 10));
      return true;
    }
  }
  return QMainWindow::eventFilter(watched, event);
}

MainWindow::~MainWindow() { delete ui; }
