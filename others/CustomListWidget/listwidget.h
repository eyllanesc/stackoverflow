#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>

class ListWidget : public QListWidget {
  Q_OBJECT
public:
  explicit ListWidget(QWidget *parent = 0);

signals:
  void blankSpaceClicked();

protected:
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // LISTWIDGET_H
