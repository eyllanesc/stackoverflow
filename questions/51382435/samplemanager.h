#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include "itemfiltersortmodel.h"
#include "itemmodel.h"

#include <QObject>

class SampleManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(ItemModel *model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(ItemFilterProxyModel *filterModel READ filterModel NOTIFY
                 filterModelChanged)
public:
  SampleManager(QObject *parent = nullptr) : QObject(parent) {
    mProxy = new ItemFilterProxyModel(this);
  }
  ItemModel *model() const { return mModel.get(); }
  void setModel(ItemModel *model) {
    if (mModel.get() == model)
      return;
    mModel.reset(model);
    mProxy->setSourceModel(mModel.get());
    emit filterModelChanged();
  }
  ItemFilterProxyModel *filterModel() const { return mProxy; }
signals:
  void modelChanged();
  void filterModelChanged();

private:
  QScopedPointer<ItemModel> mModel;
  ItemFilterProxyModel *mProxy;
};

#endif // SAMPLEMANAGER_H
