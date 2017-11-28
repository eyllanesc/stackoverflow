#include "vehicle.h"
#include "twovector.h"
#include <iostream>
using namespace std;

Vehicle::Vehicle(){
}

Vehicle::Vehicle(TwoVector position, double velocity){
    fPosition = position;
    fVelocity = velocity;
}

Vehicle::~Vehicle(){
}

void Vehicle::SetValue(string ValueName, double Value) {
    if(ValueName.compare("Radius") == 0)
        fPosition.SetRadius(Value);
    else{
        if(ValueName.compare("Angle") == 0)
            fPosition.SetAngle(Value);
        else if(ValueName.compare("Velocity") == 0)
            fVelocity = Value;
        else
            cerr << "Unknown field entered: " << ValueName << endl;
    }

}

void Vehicle::Drive(double velocity){
    fPosition.SetAngle(fPosition.GetAngle() + (velocity)/(fPosition.GetRadius()));
}
