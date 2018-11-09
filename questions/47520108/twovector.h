#ifndef TWOVECTOR_H
#define TWOVECTOR_H
#include <math.h>

class TwoVector {
public:
    TwoVector();

    TwoVector(double radius, double theta);

    ~TwoVector();

    inline double GetX() {return fRadius*cos(fTheta);}
    inline double GetY() {return fRadius*sin(fTheta);}
    inline double GetRadius() const {return fRadius;}
    inline double GetAngle() const {return fTheta;}
        //Accessor functions, these simply return the value of the coordinates


    inline void SetRadius(double radius) {fRadius = radius;}
    inline void SetAngle(double theta) {fTheta = theta;}
    inline void SetRadiusAndAngle(double radius, double theta) {
        fRadius = radius, fTheta = theta;}
        //Mutator function to change the position

    TwoVector operator += (TwoVector);
        //Operator overloading so that vectors can be added


private:

    double fRadius;
    double fTheta;

};

#endif // TWOVECTOR_H
