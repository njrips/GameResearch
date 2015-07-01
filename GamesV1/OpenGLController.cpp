#include "OpenGLController.h"

OpenGLController::OpenGLController(){}

OpenGLController::~OpenGLController(){}

bool OpenGLController::init()
{
    GLfloat L_Pos_1[] = { 10.0, 10.0, 10.0, 1.0 };
    GLfloat L_Pos_2[] = { -10.0, 10.0, -10.0, 1.0 };
    GLfloat White_L[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat Red_L[] = { 1.0, 1.0, 1.0, 1.0 };
    glClearColor(0.10, 0.8, 0.95, 0.00);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, L_Pos_1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, White_L);
    glLightfv(GL_LIGHT0, GL_SPECULAR, White_L);

    glLightfv(GL_LIGHT1, GL_POSITION, L_Pos_2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Red_L);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Red_L);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return true;
}
