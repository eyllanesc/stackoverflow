#ifndef NAVAIDSPOINT_H
#define NAVAIDSPOINT_H

#include <QGeoCoordinate>
#include <QString>
#include <QMetaType>

class NavaidsPoint
{
public:
    enum Type{
        type1,
        type2
    };

    NavaidsPoint(double latitude, double longitude, Type type){
        m_position.setLatitude(latitude);
        m_position.setLongitude(longitude);
        m_position.setAltitude(0.0);
        m_type = type;
    }

    void setPosition(const QGeoCoordinate &c) { //Affectation des nouvelles coordonnées de position
        m_position = c;
    }

    QGeoCoordinate position() const{
        return m_position; //Lecture des coordonnées de position
    }


    Type type() const
    {
        return m_type;
    }

private:
    QGeoCoordinate m_position;
    Type m_type;
};

Q_DECLARE_METATYPE(NavaidsPoint::Type)
#endif // NAVAIDSPOINT_H

