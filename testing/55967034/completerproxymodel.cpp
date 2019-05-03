#include "completerproxymodel.h"
#include "completerdata.h"

#include <QDebug>

bool CompleterProxyModel::lessThan( const QModelIndex &p_left, const QModelIndex &p_right ) const
{
    CompleterDataRow::Type leftType = static_cast<CompleterDataRow::Type>( p_left.data( Qt::UserRole ).toInt() );
    CompleterDataRow::Type rightType = static_cast<CompleterDataRow::Type>( p_right.data( Qt::UserRole ).toInt() );

    if ( ( leftType == CompleterDataRow::Type::Data && rightType == CompleterDataRow::Type::Data ) ||
         ( leftType == CompleterDataRow::Type::LastUsed && rightType == CompleterDataRow::Type::LastUsed ) )
    {

        QString leftString = p_left.data( Qt::EditRole ).toString();
        QString rightString = p_right.data( Qt::EditRole ).toString();
        qDebug() << leftString << rightString << QString::localeAwareCompare( leftString, rightString );

        return QString::localeAwareCompare( leftString, rightString ) < 0;
    }
    return false;
}
