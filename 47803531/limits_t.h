#ifndef LIMITS_T_H
#define LIMITS_T_H

#include <QObject>

class LIMITS_T : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float min READ readMin WRITE writeMin NOTIFY minChanged)
public:
    explicit LIMITS_T(QObject *parent = nullptr): QObject(parent){

    }
    float readMin() const
    {
        return mMin;
    }
    void writeMin(float min)
    {
        mMin = min;
        emit minChanged();
    }
signals:
    void minChanged();
private:
    float mMin;
};


#endif // LIMITS_T_H
