%Import QtCore/QtCoremod.sip
class Derived: public Base
{
%TypeHeaderCode
#include "derived.h"
%End
public:
    Derived(QObject *parent=nullptr);
    QString doStuff();
};