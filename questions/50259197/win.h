#ifndef WIN_H
#define WIN_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QMultiMap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

#include "graphwidget.h"

class Win : public QWidget {
  Q_OBJECT
public:
  explicit Win(QWidget *parent = nullptr);
  ~Win();

private:
  QPushButton *btnCreateNode;
  QPushButton *btnConnectNode;
  QPushButton *btnDelete;
  GraphWidget *grafViewScene;
  Node *_source; // сохраняет вершину при нажатии на кнопку "Соединить"
  bool connFlag;
signals:

public slots:
  void onBtnConnectNodeClicked();
  void onBtnDeleteClicked();
  void sceneSelectionChanged();
};

#endif // WIN_H
