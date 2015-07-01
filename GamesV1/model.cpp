#include "model.h"
#include <ctime>

Model::Model() {
    x = 0.0; y = 0.5; z = 0.0;          // location of the model
    speed = 0.1;                        // direction/orientation of the model
    Rx = 0.0, Ry = 1.0, Rz = 0.0;       // rotation of the model
    Sx = 1.0, Sy = 1.0, Sz = 1.0;       // scale of the model
    Size = 1.0;
    angle = 0.0;
    active = false;
}

void Model::setActive(bool s) {
    active = s;
}

Model::~Model() {}

void Model::render() {
    if(active){
        glPushMatrix();
            glTranslatef(x, y, z);
            glScalef(Sx, Sy, Sz);
            glRotatef(angle, Rx, Ry, Rz);
            glutSolidCube(Size);
        glPopMatrix();
    }
}
