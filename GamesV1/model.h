#ifndef _MODEL_H_
#define _MODEL_H_
#include <cmath>
#include <GL/glut.h>

class Model {
public:
    //*********Position Components*********//
    GLfloat x, y, z;        //Specify the x, y, and z coordinates of a translation vector.

    //*********Translation Speed*********//
    GLfloat speed;

    //*********Scaling Components*********//
    GLfloat Sx, Sy, Sz, Size;

    //*********Rotater Components*********//
    GLfloat angle,          //Specifies the angle of rotation, in degrees.
            Rx, Ry, Rz;     //Specify the x, y, and z coordinates of a vector, respectively.

    bool active;

    Model();
    ~Model();

    void setActive(bool s);
    virtual void render();
};

#endif
