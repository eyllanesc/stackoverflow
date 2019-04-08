#ifndef TWOLISTSELECTION_H
#define TWOLISTSELECTION_H

#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

class TwoListSelection : public QWidget {
  Q_OBJECT
public:
  explicit TwoListSelection(QWidget *parent = nullptr) : QWidget{parent} {
    init();
    connections();
  }

  void addAvailableItems(const QStringList &items) { mInput->addItems(items); }

  QStringList seletedItems() {
    QStringList selected;
    for (int i = 0; i < mOuput->count(); i++)
      selected << mOuput->item(i)->text();
    return selected;
  }

private:
  void init() {
    QHBoxLayout *layout = new QHBoxLayout(this);
    mInput = new QListWidget;
    mOuput = new QListWidget;

    mButtonToSelected = new QPushButton(">>");
    mBtnMoveToAvailable = new QPushButton(">");
    mBtnMoveToSelected = new QPushButton("<");
    mButtonToAvailable = new QPushButton("<<");

    layout->addWidget(mInput);

    QVBoxLayout *layoutm = new QVBoxLayout;
    layoutm->addItem(
        new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layoutm->addWidget(mButtonToSelected);
    layoutm->addWidget(mBtnMoveToAvailable);
    layoutm->addWidget(mBtnMoveToSelected);
    layoutm->addWidget(mButtonToAvailable);
    layoutm->addItem(
        new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    layout->addLayout(layoutm);
    layout->addWidget(mOuput);

    mBtnUp = new QPushButton("Up");
    mBtnDown = new QPushButton("Down");

    QVBoxLayout *layoutl = new QVBoxLayout;
    layoutl->addItem(
        new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layoutl->addWidget(mBtnUp);
    layoutl->addWidget(mBtnDown);
    layoutl->addItem(
        new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    layout->addLayout(layoutl);
    setStatusButton();
  }

  void connections() {
    connect(mOuput, &QListWidget::itemSelectionChanged, this,
            &TwoListSelection::setStatusButton);
    connect(mInput, &QListWidget::itemSelectionChanged, this,
            &TwoListSelection::setStatusButton);
    connect(mBtnMoveToAvailable, &QPushButton::clicked,
            [=]() { mOuput->addItem(mInput->takeItem(mInput->currentRow())); });

    connect(mBtnMoveToSelected, &QPushButton::clicked,
            [=]() { mInput->addItem(mOuput->takeItem(mOuput->currentRow())); });

    connect(mButtonToAvailable, &QPushButton::clicked, [=]() {
      while (mOuput->count() > 0) {
        mInput->addItem(mOuput->takeItem(0));
      }
    });

    connect(mButtonToSelected, &QPushButton::clicked, [=]() {
      while (mInput->count() > 0) {
        mOuput->addItem(mInput->takeItem(0));
      }
    });

    connect(mBtnUp, &QPushButton::clicked, [=]() {
      int row = mOuput->currentRow();
      QListWidgetItem *currentItem = mOuput->takeItem(row);
      mOuput->insertItem(row - 1, currentItem);
      mOuput->setCurrentRow(row - 1);
    });

    connect(mBtnDown, &QPushButton::clicked, [=]() {
      int row = mOuput->currentRow();
      QListWidgetItem *currentItem = mOuput->takeItem(row);
      mOuput->insertItem(row + 1, currentItem);
      mOuput->setCurrentRow(row + 1);
    });
  }

  void setStatusButton() {
    mBtnUp->setDisabled(mOuput->selectedItems().isEmpty() ||
                        mOuput->currentRow() == 0);
    mBtnDown->setDisabled(mOuput->selectedItems().isEmpty() ||
                          mOuput->currentRow() == mOuput->count() - 1);
    mBtnMoveToAvailable->setDisabled(mInput->selectedItems().isEmpty());
    mBtnMoveToSelected->setDisabled(mOuput->selectedItems().isEmpty());
  }

  QListWidget *mInput;
  QListWidget *mOuput;

  QPushButton *mButtonToAvailable;
  QPushButton *mButtonToSelected;

  QPushButton *mBtnMoveToAvailable;
  QPushButton *mBtnMoveToSelected;

  QPushButton *mBtnUp;
  QPushButton *mBtnDown;
};

#endif // TWOLISTSELECTION_H
