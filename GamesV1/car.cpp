#include "car.h"

Car::Car() : Model() {}

Car::~Car() {
    gluDeleteQuadric(FRWheel);

}

void Car::FrontRightWheel() {
		glBegin(GL_POLYGON);
            gluCylinder(FRWheel, 0.5, 0.5, 0.1, 30, 15);
            glColor3f(1,0,0);
		glEnd();
}
