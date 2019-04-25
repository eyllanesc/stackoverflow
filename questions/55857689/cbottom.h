#ifndef CBOTTOM_H
#define CBOTTOM_H

#include <QObject>
class CBottom : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    CBottom(QObject *parent = nullptr) : QObject(parent){}
    CBottom(const QString& name, QObject *parent = nullptr) : QObject(parent), m_name(name){}
    void setName(const QString& name){
        if (name != m_name){
            m_name = name;
            Q_EMIT nameChanged();
        }
    }
    QString name() const{
        return m_name;
    }
Q_SIGNAL void nameChanged();
private:
    QString m_name;
};
#endif // CBOTTOM_H
