#ifndef NAVAIDSPOINT_H
#define NAVAIDSPOINT_H

#include <QGeoCoordinate>
#include <QString>

class NavaidsPoint
{
public:
    NavaidsPoint(QString code, double latitude, double longitude, QString country = ""){
        m_code = code;
        m_country = country;
        m_position.setLatitude(latitude);
        m_position.setLongitude(longitude);
        m_position.setAltitude(0.0);
    }

    void setPosition(const QGeoCoordinate &c) { //Affectation des nouvelles coordonnées de position
        m_position = c;
    }

    QGeoCoordinate position() const{
        return m_position; //Lecture des coordonnées de position
    }

    QString oaciCode() const {
        return m_code;
    }

    QString countryCode() const {
        return m_country;
    }

private:
    QGeoCoordinate m_position;
    QString m_code;
    QString m_country;
};


#endif // NAVAIDSPOINT_H
