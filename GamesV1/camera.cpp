#include "camera.h"
#include <GL/glut.h>

Camera::Camera(Model* target) {
    setCameraMode(REVOLVE_MODE);
    this->target = target;
    upX = 0.0;
    upY = 1.0;
    upZ = 0.0;
    camR = 5.0;
}

void Camera::setTarget(Model* target) {
    this->target = target;
}

void Camera::setCameraMode(const int mode) {
    camMode = mode;
}

void Camera::setCamera() {
    if(camMode==REVOLVE_MODE){
        spin += 0.01;
        camX = camR * cos(spin) + target->x;
        camY = 2.5;
        camZ = -camR * sin(spin) + target->z;
        lookX = target->x;
        lookY = target->y;
        lookZ = target->z;
        gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, upX, upY, upZ);
    }
    else
    if(camMode==THIRD_PERSON_MODE){
        camX= target->x-(camR*cos(target->angle*M_PI / 180.0));
        camY= 2.5;
        camZ= target->z+(camR*sin(target->angle*M_PI / 180.0));
        lookX = target->x;
        lookY = target->y;
        lookZ = target->z;
        gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, upX, upY, upZ);
    }
    else
    if(camMode==FIRST_PERSON_MODE){
        camX= target->x-(2*camR*cos(target->angle*M_PI / 180.0));
        camY= 10;
        camZ= target->z+(2*camR*sin(target->angle*M_PI / 180.0));
        lookX = target->x;
        lookY = target->y;
        lookZ = target->z;
        gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, upX, upY, upZ);
    }
}

