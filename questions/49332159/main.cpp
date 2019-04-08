#include <QApplication>
#include <QListWidget>
#include <QMenu>
#include <QTabWidget>
#include <QVBoxLayout>

class Widget : public QWidget {
  Q_OBJECT
  QTabWidget *lists;

public:
  Widget(QWidget *parent = Q_NULLPTR) : QWidget(parent) {
    lists = new QTabWidget;
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &Widget::customContextMenuRequested, this,
            &Widget::onCustomContextMenuRequested);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(lists);
    for (int i = 0; i < 4; i++) {
      auto list = new QListWidget;
      lists->addTab(list, QString("tab-%1").arg(i));
      for (int j = 0; j < 10; j++) {
        list->addItem(QString("item %1-%2").arg(i).arg(j));
      }
    }
  }
private slots:
  void onCustomContextMenuRequested(const QPoint &pos) {
    QPoint globalPos = mapToGlobal(pos);
    QListWidget *list = static_cast<QListWidget *>(lists->currentWidget());
    if (list) {
      QPoint p = list->viewport()->mapFromGlobal(globalPos);
      QListWidgetItem *item = list->itemAt(p);
      if (item)
        showContextMenu(item, globalPos);
    }
  }

  void showContextMenu(QListWidgetItem *item, const QPoint &globalPos) {
    QMenu menu;
    menu.addAction(item->text());
    menu.exec(globalPos);
  }
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;
  w.show();

  return a.exec();
}

#include "main.moc"
