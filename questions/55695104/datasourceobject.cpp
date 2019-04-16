#include "datasourceobject.h"


DataSourceObject::DataSourceObject(int id, const QString &name, const QString &displayname, double value):
 m_id(id), m_name(name), m_unit(displayname), m_value(value)
{

}

int DataSourceObject::id() const
{
    return m_id;
}

void DataSourceObject::setId(int id)
{
    m_id = id;
}

QString DataSourceObject::name() const
{
    return m_name;
}

void DataSourceObject::setName(const QString &name)
{
    m_name = name;
}

QString DataSourceObject::unit() const
{
    return m_unit;
}

void DataSourceObject::setUnit(const QString &unit)
{
    m_unit = unit;
}

double DataSourceObject::value() const
{
    return m_value;
}

void DataSourceObject::setValue(double value)
{
    m_value = value;
}

QVariantMap DataSourceObject::toMap() const
{
    QVariantMap map;
    map["id"] = m_id;
    map["value"] = m_value;
    map["unit"] = m_unit;
    map["name"] = m_name;
    return map;
}
