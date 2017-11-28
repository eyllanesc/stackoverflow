#include "car.h"

Car::Car():Vehicle(){
}

Car::Car(TwoVector position, double velocity):Vehicle(position, velocity){
    fPositioncar = position;
    fVelocitycar = velocity;
}

Car::~Car(){
}
