#ifndef COMPLETERSOURCEMODEL_H
#define COMPLETERSOURCEMODEL_H

#include "completerdata.h"

#include <QStandardItemModel>

class CompleterSourceModel : public QStandardItemModel
{
public:
    using QStandardItemModel::QStandardItemModel;
    Qt::ItemFlags flags( const QModelIndex &index ) const override;
    void setCompleterData( const CompleterData &p_completerData );
private:
    CompleterData m_completerData;
};

#endif // COMPLETERSOURCEMODEL_H
