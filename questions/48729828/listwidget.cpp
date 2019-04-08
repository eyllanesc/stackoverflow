#include "listwidget.h"

#include <QComboBox>
#include <QDropEvent>

ListWidget::ListWidget(QWidget *parent) : QListWidget(parent) {
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDefaultDropAction(Qt::MoveAction);
}

void ListWidget::dropEvent(QDropEvent *event) {
  if (event->dropAction() == Qt::MoveAction && event->source()) {
    ListWidget *listWidget = qobject_cast<ListWidget *>(event->source());
    if (!listWidget)
      return;

    QList<QPersistentModelIndex> pIndexes;
    for (QModelIndex index : listWidget->selectedIndexes()) {
      pIndexes << QPersistentModelIndex(index);
    }

    std::sort(pIndexes.begin(), pIndexes.end());

    QListWidgetItem *item = itemAt(event->pos());
    int rowStart = item ? row(item) : count();

    for (QPersistentModelIndex pindex : pIndexes) {
      int r = QModelIndex(pindex).row();
      QComboBox *input = qobject_cast<QComboBox *>(
          listWidget->itemWidget(listWidget->item(r)));

      QComboBox *output;
      if (input) {
        // move data to QComboBox
        output = new QComboBox;
        for (int i = 0; i < input->count(); i++) {
          output->addItem(input->itemText(i));
          output->setCurrentText(input->currentText());
        }
      }

      QListWidgetItem *it = listWidget->takeItem(r);
      insertItem(rowStart, it);
      if (input)
        setItemWidget(it, output);
    }
    setState(QAbstractItemView::NoState);
  }
}

void ListWidget::mouseMoveEvent(QMouseEvent *event) {
  setState(QAbstractItemView::DraggingState);
  QListWidget::mouseMoveEvent(event);
}
