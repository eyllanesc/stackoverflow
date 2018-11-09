#ifndef MAINCPP_H
#define MAINCPP_H

#include "config.h"

#include <QObject>

class MainCpp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int someValue READ someValue NOTIFY someValueChanged)
public:
    explicit MainCpp(QObject *parent = nullptr);

    int someValue(){return m_someValue;}

    Q_INVOKABLE void update(int var);

signals:
    void someValueChanged();

private:
    int    m_someValue;
};

#endif // MAINCPP_H
