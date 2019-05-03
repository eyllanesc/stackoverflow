#ifndef COMPLETERDATA_H
#define COMPLETERDATA_H

#include <QList>
#include <QPair>
#include <QVariant>
#include <QVector>

class CompleterDataRow
{
public:
    enum class Type
    {
        Header,
        SecondHeader,
        Data,
        LastUsed
    };
    CompleterDataRow() = default;
    CompleterDataRow( const CompleterDataRow::Type p_rowType, const
                      QList<QPair<QString, QVariant>> &p_rowData );
    void setType( const CompleterDataRow::Type p_type );
    CompleterDataRow::Type type() const;
    QList<QPair<QString, QVariant>> rowData() const;
    void setRowData( const QList<QPair<QString, QVariant>> &p_rowData );

private:
    QList<QPair<QString, QVariant>> m_rowData;
    Type m_type;
};

class CompleterData
{
public:
    CompleterData() = default;
    QVector<CompleterDataRow> data() const;
    void setData( const QVector<CompleterDataRow> &p_data );
    void addData( const CompleterDataRow &p_rowData );
    void removeData( int p_row );
    void setHeaders( const QStringList &p_headers );
    void setTitle( const QString &p_label );
    const QStringList &headers() const;
    const QString &title() const;

private:
    QVector<CompleterDataRow> m_completerData;
    QString m_title;
    QStringList m_headers;
};
#endif // COMPLETERDATA_H
