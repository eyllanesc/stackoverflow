#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QTreeView>

enum CustomRoles { SelectRole = Qt::UserRole };

class EditorWidget : public QWidget {
  Q_OBJECT
public:
  EditorWidget(QWidget *parent = nullptr)
      : QWidget(parent), checkBox(new QCheckBox), lineBox(new QLineEdit),
        comboBox(new QComboBox) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    comboBox->addItems({"item1", "item2", "item3"});
    layout->addWidget(checkBox);
    layout->addWidget(lineBox);
    layout->addWidget(comboBox);
  }

  int currentIndex() { return comboBox->currentIndex(); }
  void setCurrentIndex(int index) { comboBox->setCurrentIndex(index); }
  QString text() const { return lineBox->text(); }
  void setText(const QString &text) { lineBox->setText(text); }
  Qt::CheckState checkState() const { return checkBox->checkState(); }
  void setCheckState(Qt::CheckState state) { checkBox->setCheckState(state); }

private:
  QCheckBox *checkBox;
  QLineEdit *lineBox;
  QComboBox *comboBox;
};

class Delegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  using QStyledItemDelegate::QStyledItemDelegate;
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const {
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(index)
  }
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const {
    Q_UNUSED(option)
    Q_UNUSED(index)
    EditorWidget *editor = new EditorWidget(parent);
    return editor;
  }
  void setEditorData(QWidget *editor, const QModelIndex &index) const {
    EditorWidget *widget = static_cast<EditorWidget *>(editor);
    widget->blockSignals(true);
    widget->setText(index.data(Qt::DisplayRole).toString());
    Qt::CheckState state =
        static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
    widget->setCheckState(state);
    widget->setCurrentIndex(index.data(CustomRoles::SelectRole).toInt());
    widget->blockSignals(false);
  }
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const {
    EditorWidget *widget = static_cast<EditorWidget *>(editor);
    model->setData(index, widget->text(), Qt::DisplayRole);
    model->setData(index, widget->checkState(), Qt::CheckStateRole);
    model->setData(index, widget->sizeHint(), Qt::SizeHintRole);
    model->setData(index, widget->currentIndex(), CustomRoles::SelectRole);
  }
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const {
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
  }
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const {
    QSize s = index.data(Qt::SizeHintRole).toSize();
    return s.isValid() ? s : QStyledItemDelegate::sizeHint(option, index);
  }
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTreeView treeView;
  QStandardItemModel model(4, 2);
  treeView.setModel(&model);

  Delegate delegate;
  treeView.setItemDelegate(&delegate);

  treeView.header()->setSectionResizeMode(QHeaderView::ResizeToContents);
  treeView.setRootIsDecorated(false);
  treeView.setHeaderHidden(true);
  treeView.setIndentation(20);
  for (int row = 0; row < 4; ++row) {
    for (int column = 0; column < 2; ++column) {
      QModelIndex index = model.index(row, column, QModelIndex());
      model.setData(index, QVariant((row + 1) * (column + 1)));
      treeView.openPersistentEditor(index);
    }
  }
  treeView.resize(treeView.sizeHint());
  treeView.show();

  return a.exec();
}

#include "main.moc"
