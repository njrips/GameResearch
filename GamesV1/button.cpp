#include "button.h"

Button::Button(char* text){
    str = text;
}

Button::~Button(){}

void Button::setHover(bool h){
    hover = h;
}

bool Button::isHover(float xPos, float yPos){
    if(xPos >= Xmin && xPos <= Xmax){
        if(yPos >= Ymin-95 && yPos <= Ymax-105){
            return true;
        }
    }
    return false;
}

void Button::setPos(float a, float b){
    x = a;
    y = b;
    Xmax = x + 40;
    Xmin = x - 40;
    Ymax = y + 20;
    Ymin = y - 20;
    int len, i;
    len = strlen(str);
    if(!hover){
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2f(Xmin+15.0, Ymax-10.0);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        }

        glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(Xmin+3, Ymin+3, 0);
            glVertex3f(Xmin+3, Ymax-1, 0);
            glVertex3f(Xmax-1, Ymax-1, 0);
            glVertex3f(Xmax-1, Ymin+3, 0);
        glEnd();

        glBegin(GL_QUADS);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(Xmax, Ymin, 0);
            glVertex3f(Xmin, Ymin, 0);
            glVertex3f(Xmin, Ymax, 0);
            glVertex3f(Xmax, Ymax, 0);
        glEnd();
    }else{
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(Xmin+15.0, Ymax-10.0);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        }

        glBegin(GL_QUADS);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(Xmin+3, Ymin+3, 0);
            glVertex3f(Xmin+3, Ymax-1, 0);
            glVertex3f(Xmax-1, Ymax-1, 0);
            glVertex3f(Xmax-1, Ymin+3, 0);
        glEnd();

        glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 1.0);
            glVertex3f(Xmax, Ymin, 0);
            glVertex3f(Xmin, Ymin, 0);
            glVertex3f(Xmin, Ymax, 0);
            glVertex3f(Xmax, Ymax, 0);
        glEnd();
    }
}
