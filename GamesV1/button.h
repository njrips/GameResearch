#ifndef BUTTON_H
#define BUTTON_H

#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <cstring>
#include <stdio.h>

class Button {
	public:
		Button(char* text);
		~Button();

        float x, y;
        float Xmax, Xmin, Ymax, Ymin;

		bool hover = false;

		char* str;
        void setPos(float a, float b);
        void setHover(bool h);
        bool isHover(float xPos, float yPos);
    private:
};

#endif
