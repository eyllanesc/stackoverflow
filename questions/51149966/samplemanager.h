#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include "samplemodel.h"

#include <QObject>

class SampleManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(SampleModel *model READ model WRITE setModel NOTIFY modelChanged)
public:
  using QObject::QObject;
  SampleModel *model() const { return mModel.get(); }
  void setModel(SampleModel *model) {
    if (mModel.get() == model)
      return;
    mModel.reset(model);
  }
signals:
  void modelChanged();

private:
  QScopedPointer<SampleModel> mModel;
};

#endif // SAMPLEMANAGER_H
