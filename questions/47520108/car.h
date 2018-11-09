#ifndef CAR_H
#define CAR_H
#include "twovector.h"
#include "vehicle.h"
#include <iostream>
using namespace std;

class Car: public Vehicle {
public:
    Car();

    Car(TwoVector position, double velocity);

    ~Car();

private:

    TwoVector fPositioncar;
    double fVelocitycar;

};

#endif // CAR_H
