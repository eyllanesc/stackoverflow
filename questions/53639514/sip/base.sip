%Import QtCore/QtCoremod.sip
class Base: public QObject
{
%TypeHeaderCode
#include "base.h"
%End
public:
    Base(QObject *parent=nullptr);
    virtual QString doStuff();
};
