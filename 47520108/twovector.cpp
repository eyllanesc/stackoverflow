#include "twovector.h"

TwoVector::TwoVector(){
    fRadius = 0;
    fTheta = 0;
}

TwoVector::TwoVector(double radius, double theta){
    fRadius = radius;
    fTheta = theta;
}

TwoVector::~TwoVector(){
}

TwoVector TwoVector::operator +=(TwoVector position1){
    TwoVector position2;
        //Creates a new object which is given a position
    position2.fRadius = sqrt(((fRadius)*(fRadius))+((position1.fRadius)*(position1.fRadius))
                             + 2*((position1.fRadius)*(fRadius))*cos((position1.fTheta)-(fTheta)));
    position2.fTheta = fTheta + atan2((position1.fRadius)*(sin((position1.fTheta)-(fTheta))),
                                 fRadius + (position1.fRadius)*(cos((position1.fTheta)-fTheta)));
    return(position2);
    //New position returned

}
