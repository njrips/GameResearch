#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "model.h"

class Camera {
public:
    float camX, camY, camZ;
    float lookX, lookY, lookZ;
    float upX, upY, upZ;
    float camR;
    int camMode;
    float spin;

    Model *target;

    static const int FIXED_MODE = 0;
    static const int REVOLVE_MODE = 1;
    static const int THIRD_PERSON_MODE = 2;
    static const int FIRST_PERSON_MODE = 3;

    Camera(Model *target);
    void setCameraMode(const int mode);
    void setCamera();
    void setTarget(Model *target);
};

#endif
