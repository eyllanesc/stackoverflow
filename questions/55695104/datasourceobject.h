#ifndef DATASOURCEOBJECT_H
#define DATASOURCEOBJECT_H

#include <QVariantMap>
class QString;
class QJsonObject;

class DataSourceObject
{
public:
    DataSourceObject(int id=0, const QString &name="", const QString &displayname="", double value=0.0);
    // DataSourceObject(const QJsonObject &obj);
    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString unit() const;
    void setUnit(const QString &unit);

    double value() const;
    void setValue(double value);

    QVariantMap toMap() const;

private:
    int m_id;
    QString m_name;
    QString m_unit;
    double m_value;
};
#endif // DATASOURCEOBJECT_H
