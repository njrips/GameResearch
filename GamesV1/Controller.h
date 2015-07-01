#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<GL/gl.h>

#include "SDLController.h"
#include "OpenGLController.h"
#include "imageloader.h"
#include "camera.h"
#include "button.h"
#include "car.h"

SDLController* gameWindow;
OpenGLController* graphicsSetup;
Camera* camera;
Model* model;
Button* start;
Car* racer;

bool quit;

bool fullScreen = false;

bool gameStart = false;

GLuint texture;

GLuint road; //The id of the texture

GLdouble    fovy = 45,          //Specifies the field of view angle, in degrees, in the y direction.
            zNear = 0.1,        //Specifies the distance from the viewer to the near clipping plane (always positive).
            zFar = 200.0;       //Specifies the distance from the viewer to the far clipping plane (always positive).

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void controllScreen() {

    float left = 0.0;
    float right = gameWindow->getWidth();
    float top = 0.0;
    float bottom = gameWindow->getHeight();

    float mapLeft = left;
    float mapRight = left+right/4;
    float mapTop = bottom-bottom/4;
    float mapBottom = bottom;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_LIGHTING);

    if(gameStart){
        //************* MAP ************//
        char* str;
        str = "Racing Map";
        int len, i;
        len = strlen(str);

        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2f(mapRight/3, mapTop+20);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
        }

        glBegin(GL_QUADS);
            glColor3f(1.0,1.0,0.0);
            glVertex2f( mapLeft, mapTop);
            glVertex2f( mapLeft, mapTop+3.0);
            glVertex2f( mapRight+3.0, mapTop+3.0);
            glVertex2f( mapRight+3.0, mapTop);
            glColor3f(1.0,1.0,0.0);
            glVertex2f( mapRight, mapTop);
            glVertex2f( mapRight+3.0, mapTop);
            glVertex2f( mapRight+3.0, mapBottom);
            glVertex2f( mapRight, mapBottom);
            glColor4f(0.0, 0.0, 0.0, 0.7);
            glVertex3f(mapLeft, mapBottom, 0);
            glVertex3f(mapRight, mapBottom, 0);
            glVertex3f(mapRight, mapTop, 0);
            glVertex3f(mapLeft, mapTop, 0);
        glEnd();

        //************* Console ************//
        glBegin(GL_QUADS);
            glColor3f(1.0,0.0,0.0);
            glVertex2f( mapRight+3.0, mapTop+50);
            glVertex2f( right, mapTop+50);
            glVertex2f( right, mapTop+53);
            glVertex2f( mapRight+3.0, mapTop+53);
            glColor4f(0.0, 0.0, 0.0, 0.7);
            glVertex3f(mapRight+3.0, mapBottom, 0);
            glVertex3f(mapRight+3.0, mapTop+50, 0);
            glVertex3f(right, mapTop+50, 0);
            glVertex3f(right, mapBottom, 0);
        glEnd();
    }else{
        //************* button ************//
        start->setPos(gameWindow->getWidth()/2, gameWindow->getHeight()/2);
    }

    glEnable(GL_LIGHTING);
}

void keyEvent(SDL_Keycode key, SDL_Scancode scan )
{
    switch( scan )
    {
        case SDL_SCANCODE_C:
            (camera->camMode == 1) ? camera->setCameraMode(2) : (camera->camMode == 2) ? camera->setCameraMode(3) : camera->setCameraMode(1);
            break;
        case SDL_SCANCODE_F:
            if(!fullScreen){
                SDL_SetWindowFullscreen(gameWindow->myWindow, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
                fullScreen = true;
            }
            printf( "SDL_SCANCODE_F key Pressed!\n" );
            break;
        case SDL_SCANCODE_ESCAPE:
            (fullScreen) ? SDL_SetWindowFullscreen(gameWindow->myWindow, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN), fullScreen = false : quit = true;
            break;
    }

    switch( key )
    {
        case SDLK_UP:
            printf( "SDLK_UP key Pressed!\n" );
            model->x+=model->speed*cos(model->angle*M_PI / 180.0);
            break;
        case SDLK_DOWN:
            printf( "SDLK_DOWN key Pressed!\n" );
            model->x-=model->speed*cos(model->angle*M_PI / 180.0);
            break;
        case SDLK_LEFT:
            printf( "SDLK_DOWN key Pressed!\n" );
            model->angle+=model->speed;
            break;
        case SDLK_RIGHT:
            printf( "SDLK_RIGHT key Pressed!\n" );
            model->angle-=model->speed;
            break;

    }
}

void windowEvent(SDL_Event event)
{
    switch( event.window.event )
    {
        case SDL_WINDOWEVENT_SHOWN:
            printf("Window %d shown\n", event.window.event);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            printf("Window %d hidden\n", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            printf("Window %d exposed\n", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            printf("Window %d moved to %d,%d\n",
                    event.window.windowID, event.window.data1,
                    event.window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            //gameWindow->setWidth(event.window.data1);
            //gameWindow->setHeight(event.window.data2);
            //glMatrixMode(GL_MODELVIEW);
            //glLoadIdentity();
            glViewport( 0, 0, event.window.data1, event.window.data2 );
            //gluPerspective(fovy, gameWindow->getWidth() / gameWindow->getHeight(), zNear, zFar);
            printf("Window %d resized to %dx%d\n",
                    event.window.windowID, event.window.data1,
                    event.window.data2);
            printf("Window That Sized %dx%d\n",
                    gameWindow->getWidth(),
                    gameWindow->getHeight());
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            printf("Window %d minimized\n", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            printf("Window %d maximized\n", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            printf("Window %d restored\n", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            printf("Mouse entered window %d\n",
                    event.window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            printf("Mouse left window %d\n", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            printf("Window %d gained keyboard focus\n",
                    event.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            printf("Window %d lost keyboard focus\n",
                    event.window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            printf("Window %d closed\n", event.window.windowID);
            break;
        default:
            printf("Window %d got unknown event %d\n",
                    event.window.windowID, event.window.event);
            break;
    }
}

void mouseEvent(SDL_Event event)
{
    if ( event.type == SDL_MOUSEMOTION ) {
        (start->isHover(event.motion.x, event.motion.y)) ? start->setHover(true) : start->setHover(false);
    }
    if (event.type = SDL_MOUSEBUTTONDOWN) {
        if(event.button.button == SDL_BUTTON_LEFT) {
            if (event.button.state == SDL_PRESSED) {
                if(start->isHover(event.motion.x, event.motion.y))
                    gameStart = true;
            } else if(event.button.state == SDL_RELEASED) {

            }
        }
    }
}

#endif
