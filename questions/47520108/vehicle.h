#ifndef VEHICLE_H
#define VEHICLE_H
#include "twovector.h"
#include <iostream>
using namespace std;

class Vehicle
{
public:
    Vehicle();

    Vehicle(TwoVector position, double velocity);

    ~Vehicle();

    inline TwoVector GetPosition() {return fPosition;}

    inline double GetVelocity() {return fVelocity;}

    inline void SetPosition(TwoVector position) {fPosition = position;}

    void SetValue(string ValueName, double Value);

    void Drive(double velocity);

private:

    TwoVector fPosition;
    double fVelocity;
};

#endif // VEHICLE_H
