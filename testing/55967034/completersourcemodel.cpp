#include "completersourcemodel.h"

Qt::ItemFlags CompleterSourceModel::flags( const QModelIndex &p_index ) const
{
    if ( !p_index.isValid() ) {
        return Qt::NoItemFlags;
    }

    CompleterDataRow::Type type = m_completerData.data().at( p_index.row() ).type();
    if ( type == CompleterDataRow::Type::Data || type == CompleterDataRow::Type::LastUsed ) {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
    return Qt::NoItemFlags;
}

void CompleterSourceModel::setCompleterData( const CompleterData &p_completerData )
{
    m_completerData = p_completerData;
    setColumnCount( m_completerData.headers().size() + 1 );
    setRowCount( m_completerData.data().size() );

    for ( int col = 0; col <= m_completerData.headers().size(); col++ ) {
        col < m_completerData.headers().size() ? setHeaderData( col, Qt::Horizontal, m_completerData.headers().at( col ) ) : setHeaderData( col, Qt::Horizontal, {} );
    }

    for ( int row = 0; row < m_completerData.data().size(); row++ ) {
        for ( int col = 0; col <= m_completerData.headers().size(); col++ ) {
            if ( m_completerData.data().at( row ).type() == CompleterDataRow::Type::Header || m_completerData.data().at( row ).type() == CompleterDataRow::Type::SecondHeader ) {
                col == 0 ? setData( index( row, col ), m_completerData.data().at( row ).rowData().at( col ).first, Qt::EditRole ) : setData( index( row, col ), {}, Qt::EditRole );
            }
            else {
                col == m_completerData.headers().size() ? setData( index( row, col ), {}, Qt::EditRole ) : setData( index( row, col ), m_completerData.data().at( row ).rowData().at( col ).first, Qt::EditRole );
            }
            setData( index( row, col ), QVariant( static_cast<int>( m_completerData.data().at( row ).type() ) ), Qt::UserRole );
        }
    }
}
