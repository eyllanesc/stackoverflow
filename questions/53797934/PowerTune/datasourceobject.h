#ifndef DATASOURCEOBJECT_H
#define DATASOURCEOBJECT_H

#include <QString>
#include <QVariantMap>

class DataSourceObject {
public:
  DataSourceObject(const int &id = 0, const QString &name = "",
                   const QString &displayname = "", const double &value = 0.0);
  DataSourceObject(const QJsonObject &obj);
  int id() const;
  void setId(int id);

  QString name() const;
  void setName(const QString &name);

  QString displayname() const;
  void setDisplayname(const QString &displayname);

  double value() const;
  void setValue(double value);
  QVariantMap toMap() const;

private:
  int m_id;
  QString m_name;
  QString m_displayname;
  double m_value;
};

#endif // DATASOURCEOBJECT_H
