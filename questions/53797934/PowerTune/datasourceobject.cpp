#include "datasourceobject.h"

#include <QJsonObject>

DataSourceObject::DataSourceObject(const int &id, const QString &name,
                                   const QString &displayname,
                                   const double &value)
    : m_id(id), m_name(name), m_displayname(displayname), m_value(value) {}

DataSourceObject::DataSourceObject(const QJsonObject &obj) {
  setId(obj.value("id").toInt());
  setName(obj.value("name").toString());
  setDisplayname(obj.value("displayname").toString());
  setValue(0.0);
}

int DataSourceObject::id() const { return m_id; }

void DataSourceObject::setId(int id) { m_id = id; }

QString DataSourceObject::name() const { return m_name; }

void DataSourceObject::setName(const QString &name) { m_name = name; }

QString DataSourceObject::displayname() const { return m_displayname; }

void DataSourceObject::setDisplayname(const QString &displayname) {
  m_displayname = displayname;
}

double DataSourceObject::value() const { return m_value; }

void DataSourceObject::setValue(double value) { m_value = value; }

QVariantMap DataSourceObject::toMap() const {
  QVariantMap map;
  map["id"] = m_id;
  map["name"] = m_name;
  map["displayname"] = m_displayname;
  map["value"] = m_value;
  return map;
}
