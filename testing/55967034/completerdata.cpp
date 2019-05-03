#include "completerdata.h"

CompleterDataRow::CompleterDataRow( const CompleterDataRow::Type p_rowType, const QList<QPair<QString, QVariant>> &p_rowData )
{
    m_type = p_rowType;
    m_rowData = p_rowData;
}

QList<QPair<QString, QVariant>> CompleterDataRow::rowData() const
{
    return m_rowData;
}

void CompleterDataRow::setRowData( const QList<QPair<QString, QVariant>> &p_rowData )
{
    m_rowData = p_rowData;
}

CompleterDataRow::Type CompleterDataRow::type() const
{
    return m_type;
}

void CompleterDataRow::setType( const Type p_type )
{
    m_type = p_type;
}

QVector<CompleterDataRow> CompleterData::data() const
{
    return m_completerData;
}

void CompleterData::addData( const CompleterDataRow &p_rowData )
{
    m_completerData.append( p_rowData );
}

void CompleterData::removeData( int p_row )
{
    m_completerData.remove( p_row );
}

void CompleterData::setData( const QVector<CompleterDataRow> &p_data )
{
    m_completerData = p_data;
}

void CompleterData::setTitle( const QString &p_title )
{
    m_title = p_title;
}

const QString &CompleterData::title() const
{
    return m_title;
}

void CompleterData::setHeaders( const QStringList &p_headers )
{
    m_headers = p_headers;
}

const QStringList &CompleterData::headers() const
{
    return m_headers;
}
