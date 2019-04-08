#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>

class ListWidget : public QListWidget {
  Q_OBJECT
public:
  ListWidget(QWidget *parent = 0);
  void dropEvent(QDropEvent *event);

protected:
  void mouseMoveEvent(QMouseEvent *event);
};
#endif // LISTWIDGET_H
