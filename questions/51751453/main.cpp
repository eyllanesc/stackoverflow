#include "tablemodel.h"

#include <QApplication>
#include <QMouseEvent>
#include <QTableView>

class TableView : public QTableView {
public:
  TableView(QWidget *parent = nullptr) : QTableView(parent) {
    setMouseTracking(true);
  }

protected:
  void mouseMoveEvent(QMouseEvent *event) {
    QModelIndex ix = indexAt(event->pos());
    if (mRow != ix.row()) {
      changeRowColor(mRow);
      if (ix.isValid())
        changeRowColor(ix.row(), Qt::green, Qt::blue);
      mRow = ix.row();
    }
    QTableView::mouseMoveEvent(event);
  }

  void leaveEvent(QEvent *event) {
    changeRowColor(mRow);
    QTableView::leaveEvent(event);
  }

private:
  void changeRowColor(int row, const QColor &textColor = Qt::black,
                      const QColor &backgroundColor = Qt::white) {
    if (!model())
      return;
    for (int i = 0; i < model()->columnCount(); i++) {
      model()->setData(model()->index(row, i), textColor, Qt::ForegroundRole);
      model()->setData(model()->index(row, i), backgroundColor,
                       Qt::BackgroundRole);
    }
  }
  int mRow = -1;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TableView w;
  TableModel model(5, 5);
  for (int i = 0; i < model.rowCount(); i++) {
    for (int j = 0; j < model.columnCount(); j++) {
      model.setData(model.index(i, j), QString("%1-%2").arg(i).arg(j));
    }
  }
  w.setModel(&model);
  w.show();
  return a.exec();
}
