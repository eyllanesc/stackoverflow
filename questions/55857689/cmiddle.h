#ifndef CMIDDLE_H
#define CMIDDLE_H

#include "cbottom.h"

#include <QObject>
#include <QVector>

class CMiddle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    CMiddle(QObject *parent = nullptr) : QObject(parent){}
    CMiddle(const QString& name, const QStringList& bottoms, QObject *parent = nullptr) : QObject(parent), m_name(name){
        for(auto bottom : bottoms){
            m_bottoms.append(new CBottom(bottom));
        }
    }
    QString name() const{
        return m_name;
    }
    void setName(const QString& name){
        if (name != m_name){
            m_name = name;
            emit nameChanged();
        }
    }
Q_SIGNAL void nameChanged();
private:
    QString m_name;
    QVector<CBottom*> m_bottoms;
};

#endif // CMIDDLE_H
