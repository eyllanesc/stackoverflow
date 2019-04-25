#ifndef CTOP_H
#define CTOP_H

#include "cmiddle.h"

#include <QObject>
#include <QVector>
#include <QDebug>

class CTop : public QObject
{
    Q_OBJECT
public:
    CTop(QObject *parent = nullptr) : QObject(parent){}
    CTop(const QStringList& middles, QObject *parent = nullptr) : QObject(parent){
        int i=0;
        for(auto middle : middles){
            QStringList bottoms;
            bottoms.append("A" + QString(i));
            bottoms.append("B" + QString(i));
            bottoms.append("C" + QString(i));
            i++;
            m_middles.append(new CMiddle(middle, bottoms));
        }
    }
    Q_INVOKABLE QList<QObject*> middles(){
        QList<QObject*> objects;
        for(CMiddle *m : qAsConst(m_middles)){
            objects << m;
        }
        return objects;
    }
    Q_INVOKABLE CMiddle* middle(const int index){
        if(index >= 0 && index < m_middles.size())
            return m_middles[index];
        return nullptr;
    }
private:
    QVector<CMiddle*> m_middles;
};

#endif // CTOP_H
