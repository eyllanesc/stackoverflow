#include "QMainWidget.h"
#include "ui_QMainWidget.h"

// Qt
#include <QInputDialog>
#include <QTreeView>

QMainWidget::QMainWidget(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::QMainWidget), n_loaded_(0) {
  // Set up Ui
  ui->setupUi(this);
  // Data tree
  tree_view_model_ = new QDataItemTree("Root");
  ui->treeView->setModel(tree_view_model_);

  // Connect load
  connect(ui->addElementsLoad_pushButton, SIGNAL(clicked()), this,
          SLOT(load()));
  connect(ui->addElementsLoad2_pushButton, SIGNAL(clicked()), this,
          SLOT(load2()));
}

QMainWidget::~QMainWidget() { delete ui; }

void QMainWidget::load() {
  // How many elements to add
  int n_elements =
      QInputDialog::getInt(this, "Elements", "How many elemtns?", 10);

  // How many childs per element
  int n_childs_per_element =
      QInputDialog::getInt(this, "Elements", "How many elemtns?", 10);

  // Add batch to tree
  QDataItem *batch = tree_view_model_->addBatch(n_loaded_);
  for (int i = 0; i < n_elements; i++) {
    QDataItem *element = tree_view_model_->addBatchElement(i, batch);
    for (int j = 0; j <= n_childs_per_element; j++) {
      tree_view_model_->addBatchElementChild(j, element);
    }
  }
  n_loaded_++;
  ui->treeView->setModel(tree_view_model_);
}

void QMainWidget::load2() {
  // How many elements to add
  int n_elements =
      QInputDialog::getInt(this, "Elements", "How many elemtns?", 10);

  // How many childs per element
  int n_childs_per_element =
      QInputDialog::getInt(this, "Elements", "How many elemtns?", 10);

  // Add batch to tree
  tree_view_model_ = new QDataItemTree("Root");
  QDataItem *batch = tree_view_model_->addBatch(n_loaded_);
  for (int i = 0; i < n_elements; i++) {
    QDataItem *element = tree_view_model_->addBatchElement(i, batch);
    for (int j = 0; j <= n_childs_per_element; j++) {
      tree_view_model_->addBatchElementChild(j, element);
    }
  }
  n_loaded_++;
  ui->treeView->setModel(tree_view_model_);
}
