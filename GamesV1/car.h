#ifndef _CAR_H_
#define _CAR_H_
#include "model.h"

class Car : public Model {
    public:
        Car();
        ~Car();
        GLUquadricObj *FRWheel = gluNewQuadric();
        GLUquadricObj *FLWheel = gluNewQuadric();
        GLUquadricObj *BRWheel = gluNewQuadric();
        GLUquadricObj *BLWheel = gluNewQuadric();
        float carHeading;
        float carSpeed;
        float steerAngle;
        float wheelBase; // the distance between the two axles
        void FrontRightWheel();
        void FrontLeftWheel();
        void BackRightWheel();
        void BackLeftWheel();
        void CarBody();
};

#endif
