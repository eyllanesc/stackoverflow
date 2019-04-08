#include "win.h"

Win::Win(QWidget *parent) : QWidget(parent), _source(nullptr), connFlag(false) {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  {
    QHBoxLayout *layout = new QHBoxLayout(parent);
    btnCreateNode = new QPushButton("Add a vertex", this);
    layout->addWidget(btnCreateNode);
    btnConnectNode = new QPushButton("Connect", this);
    btnConnectNode->setEnabled(false);
    layout->addWidget(btnConnectNode);
    btnDelete = new QPushButton("Remove", this);
    btnDelete->setEnabled(false);
    layout->addWidget(btnDelete);
    mainLayout->addLayout(layout);
  }
  grafViewScene = new GraphWidget(this);
  mainLayout->addWidget(grafViewScene);
  connect(btnCreateNode, &QPushButton::clicked, grafViewScene,
          &GraphWidget::addNode);
  connect(btnConnectNode, &QPushButton::clicked, this,
          &Win::onBtnConnectNodeClicked);
  connect(btnDelete, &QPushButton::clicked, this, &Win::onBtnDeleteClicked);
  connect(grafViewScene->scene(), &QGraphicsScene::selectionChanged, this,
          &Win::sceneSelectionChanged);
}

Win::~Win() {}

void Win::onBtnConnectNodeClicked() {
  _source =
      qgraphicsitem_cast<Node *>(grafViewScene->scene()->selectedItems().at(0));
  if (_source) {
    connFlag = true;
    grafViewScene->scene()->clearSelection();
  } else {
    connFlag = false;
  }
}

void Win::onBtnDeleteClicked() {
  _source = nullptr;
  connFlag = false;
  auto i = grafViewScene->scene()->selectedItems().at(0);
  grafViewScene->scene()->removeItem(i);
  delete i;
}

void Win::sceneSelectionChanged() {
  QList<QGraphicsItem *> l = grafViewScene->scene()->selectedItems();
  if (l.size() > 0) {
    Node *dest = qgraphicsitem_cast<Node *>(l.at(0));
    if (dest) {
      if (connFlag) {
        grafViewScene->scene()->addItem(new Edge(_source, dest));
        connFlag = false;
        _source = nullptr;
        btnCreateNode->setEnabled(true);
      }
      btnConnectNode->setEnabled(true);
      btnDelete->setEnabled(true);
    } else {
      connFlag = false;
      _source = nullptr;
      btnConnectNode->setEnabled(false);
      btnDelete->setEnabled(true);
    }
  } else {
    if (connFlag)
      btnCreateNode->setEnabled(false);
    else
      btnCreateNode->setEnabled(true);
    btnConnectNode->setEnabled(false);
    btnDelete->setEnabled(false);
  }
}
