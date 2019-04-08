#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include "sample.h"

#include <QAbstractListModel>

class SampleModel : public QAbstractListModel {
  Q_OBJECT
public:
  using QAbstractListModel::QAbstractListModel;
  ~SampleModel() {
    qDeleteAll(mSamples);
    mSamples.clear();
  }
  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    if (parent.isValid())
      return 0;
    return mSamples.size();
  }

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    if (!index.isValid())
      return QVariant();
    if (role == Qt::UserRole) {
      Sample *sample = mSamples[index.row()];
      return QVariant::fromValue(sample);
    }
    return QVariant();
  }

  void appendSample(Sample *sample) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mSamples << sample;
    endInsertRows();
  }

  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "sample";
    return roles;
  }

private:
  QList<Sample *> mSamples;
};

#endif // SAMPLEMODEL_H
