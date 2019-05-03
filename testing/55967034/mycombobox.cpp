#include "completerproxymodel.h"
#include "completersourcemodel.h"
#include "mycombobox.h"

#include <QTreeView>

MyComboBox::MyComboBox( QWidget *p_parent ) :
    QComboBox( p_parent ),
    m_view(new QTreeView),
    m_sourceModel(new CompleterSourceModel{this}),
    m_proxyModel(new CompleterProxyModel{this})
{
    setEditable( true );

    m_sourceModel->setCompleterData( createTestData() );
    m_proxyModel->setSourceModel(m_sourceModel);
    setModel( m_proxyModel );
    // setModel(m_sourceModel);
    setView( m_view );
    m_view->setSortingEnabled(true);
}

void MyComboBox::setDataForCompleter( const CompleterData &p_data )
   {
      if ( !p_data.data().isEmpty() )
      {
         setProperty( "hasData", true );
      }
      m_sourceModel->setCompleterData( p_data );
   }

CompleterData MyComboBox::createTestData()
{
    CompleterData data;
    data.addData( CompleterDataRow( CompleterDataRow::Type::Header, { { "Last Used", {} } } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::Data, { { "FBI", {} }, { "Female Body Inspector", {} } } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::Data, { { "PIG", {} }, { "Pretty Insensitive Guy", {} } } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::Header, { { "Something", {}} } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::LastUsed, { { "ADIDAS", {} }, {"All Day I Dream About Soccer", {} } } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::LastUsed, { { "DIET", {}}, {"Do I eat today?", {}} } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::Data, { { "TEAM", {} }, { "Together Everyone Achieves More", {} } } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::SecondHeader, { { "Lorem Ipsum", {} } } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::LastUsed, { { "CLASS", {}}, {"Come late and start sleeping", {}} } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::LastUsed, { { "PMS", {}}, {"Purchase More Shoes", {}} } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::LastUsed, { { "PwC", {}}, {"Partner want Cash", {}} } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::Header, { { "Some Countries", {} } } ) );
    data.addData( CompleterDataRow( CompleterDataRow::Type::SecondHeader, { { "Some Cities", {} } } ) );
    data.setTitle( "Proposal List" );
    data.setHeaders( { "Abbreviation", "Meaning" } );
    return data;
}
