#include "optionlist.h"

#include <QDrag>

OptionList::OptionList(QWidget *parent) : QListWidget(parent) {

  setDragEnabled(true);
  setDropIndicatorShown(true);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setDefaultDropAction(Qt::CopyAction);
  setViewMode(QListView::ListMode);

  for (const QString &color : {"Blue", "Red", "Green", "Yellow"}) {
    QListWidgetItem *blue = new QListWidgetItem;
    blue->setText(color);
    blue->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable |
                   Qt::ItemIsDragEnabled);
    addItem(blue);
  }
}

void OptionList::startDrag(Qt::DropActions supportedActions) {
  if (supportedActions & Qt::CopyAction) {
    QList<QListWidgetItem *> m_items = selectedItems();
    if (m_items.isEmpty())
      return;
    QMimeData *data = mimeData(m_items);
    QDrag *drag = new QDrag(this);
    QPixmap pixmap(":/images/MyIcon_icon.png");
    drag->setPixmap(pixmap);
    drag->setMimeData(data);
    drag->setHotSpot(pixmap.rect().center());
    drag->exec(Qt::CopyAction);
  } else
    QListWidget::startDrag(supportedActions);
}
