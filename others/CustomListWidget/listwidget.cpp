#include "listwidget.h"

#include <QDebug>
#include <QMouseEvent>

ListWidget::ListWidget(QWidget *parent) : QListWidget(parent) {}

void ListWidget::mouseReleaseEvent(QMouseEvent *event) {
  if (!isVisible())
    return;
  bool status = true;
  QAbstractItemModel *m = model();
  for (int i = 0; i < m->rowCount(); i++)
    for (int j = 0; j < m->columnCount(); j++) {
      QModelIndex index = m->index(i, j);
      QRect r = visualRect(index);
      if (r.contains(event->pos())) {
        status = false;
        break;
      }
    }
  if (status)
    emit(blankSpaceClicked());
}
