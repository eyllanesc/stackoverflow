#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>

#include <QDebug>

struct Position{
    int row;
    int column;

    bool operator==(const Position& p) const
    {
        return row == p.row && column == p.column;
    }
};

class ItemDelegate : public QItemDelegate
{
    Q_OBJECT
    QStringList items = QStringList()<<"option1"<<"option2"<<"option3";
public:
    enum TypeItemDelegate{
        DefaultType,
        ComBoboxType,
        BooleanType
    };

    ItemDelegate(const QHash<TypeItemDelegate, QVector<Position>> &positions, QObject *parent = Q_NULLPTR):QItemDelegate(parent)
    {
        mPositions = positions;
    }

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        const TypeItemDelegate type = getType(index);

        if(type == ComBoboxType){
            QComboBox* editor = new QComboBox(parent);
            editor->addItems(items);
            return editor;
        }
        else if(type == BooleanType){
            QCheckBox* editor = new QCheckBox(parent);
            editor->setChecked(false);
            return editor;
        }
        else
            return QItemDelegate::createEditor(parent, option, index);

    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        const TypeItemDelegate type = getType(index);

        if(type == ComBoboxType){
            QComboBox *comboBox = static_cast<QComboBox*>(editor);
            int value = index.model()->data(index, Qt::EditRole).toUInt();
            comboBox->setCurrentIndex(value);
        }
        else if(type == BooleanType){
            QCheckBox* checkbox = static_cast<QCheckBox*>(editor);
            bool value = index.model()->data(index, Qt::EditRole).toBool();
            checkbox->setChecked(value);
        }
        else
            QItemDelegate::setEditorData(editor, index);
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        const TypeItemDelegate type = getType(index);

        if(type == ComBoboxType){
            QComboBox *comboBox = static_cast<QComboBox*>(editor);
            model->setData(index, comboBox->currentIndex(), Qt::EditRole);
        }
        else if(type == BooleanType){
            QCheckBox* checkbox = static_cast<QCheckBox*>(editor);
            model->setData(index, checkbox->isChecked(), Qt::EditRole);
        }
        else
            QItemDelegate::setModelData(editor, model, index);

    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
    {
        editor->setGeometry(option.rect);
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionViewItem myOption = option;

        const TypeItemDelegate type = getType(index);

        if(type == ComBoboxType){
            myOption.text = items[index.data(Qt::DisplayRole).toInt()];
            QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
        }
        else if(type == BooleanType){
            bool val = index.data(Qt::DisplayRole).toBool();
            myOption.text = val? "valid" : "invalid";
            QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
        }
        else
            QItemDelegate::paint(painter, option, index);

    }

    TypeItemDelegate getType(const QModelIndex &index) const{
        const Position point{index.row(), index.column()};
        for(const TypeItemDelegate key: mPositions.keys()){
            if(key<=BooleanType)
                if(mPositions[key].contains(point))
                    return key;
        }
        return DefaultType;
    }

private:
    QHash<TypeItemDelegate, QVector<Position>> mPositions;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView view;

    QStandardItemModel model(5,3);

    view.setModel(&model);

    QHash<ItemDelegate::TypeItemDelegate, QVector<Position>> pos;

    pos[ItemDelegate::ComBoboxType] = QVector<Position>()<< Position{0, 0}<<Position{1, 1}<<Position{2, 0}<<Position{3, 1};
    pos[ItemDelegate::BooleanType] = QVector<Position>()<< Position{0, 1}<<Position{1, 0}<<Position{2, 1}<<Position{3, 0};

    ItemDelegate *delegate = new ItemDelegate(pos);
    view.setItemDelegate(delegate);

    view.horizontalHeader()->setStretchLastSection(true);
    view.show();

    return a.exec();
}
