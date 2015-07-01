#include "Controller.h"
#include <math.h>

void roadSetup(){
    float xA = 0.0;
    float yA = 0.0;
    float xB = 0.0;
    float yB = 8.0;
    float delX = xB-xA;
    float delY = yB-yA;
    float roadAngle = atan2(delY, delX) * 180 / M_PI;

    Image* image = loadBMP("LowRoad.bmp");
    road = loadTexture(image);

    glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, road);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glPushMatrix();
            glTranslatef(0.0, 0.01, 0.0);
            glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
            //glRotatef( -90.0f, 0.0f, 0.0f, 1.0f );
            glRotatef( roadAngle, 0.0f, 0.0f, 1.0f );
            glBegin( GL_QUADS );
                glTexCoord2d(0.0,0.0); glVertex2d(xA-1.0,yA-((yB-yA)/2));
                glTexCoord2d(1.0,0.0); glVertex2d(xA+1.0,yA-((yB-yA)/2));
                glTexCoord2d(1.0,1.0); glVertex2d(xA+1.0,yA+((yB-yA)/2));
                glTexCoord2d(0.0,1.0); glVertex2d(xA-1.0,yA+((yB-yA)/2));
            glEnd();
            glBegin( GL_QUADS );
                glTexCoord2d(0.0,0.0); glVertex2d(xB-1.0,yB-((yB-yA)/2));
                glTexCoord2d(1.0,0.0); glVertex2d(xB+1.0,yB-((yB-yA)/2));
                glTexCoord2d(1.0,1.0); glVertex2d(xB+1.0,yB+((yB-yA)/2));
                glTexCoord2d(0.0,1.0); glVertex2d(xB-1.0,yB+((yB-yA)/2));
            glEnd();
        glPopMatrix();
    glDisable( GL_TEXTURE_2D );
}

bool display() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, gameWindow->getWidth() / gameWindow->getHeight(), zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->setCamera();

    if(gameStart){
        //model->setActive(true);
        //model->render();
        racer->FrontRightWheel();

        glDisable(GL_LIGHTING);
        glBegin(GL_QUADS);
            glColor3f(0.20, 0.90, 0.20);
            glVertex3f(105.0, 0.0, 105.0);
            glVertex3f(-105.0, 0.0, 105.0);
            glVertex3f(-105.0, 0.0, -105.0);
            glVertex3f(105.0, 0.0, -105.0);
        glEnd();
        glEnable(GL_LIGHTING);
        roadSetup();
    }


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        controllScreen();
    glPopMatrix();
    glDisable(GL_BLEND); //and whatever to restore blending options

    glLoadIdentity();

    glFlush();

    return true;
}

int main(int argc, char* argv[]) {
    gameWindow = new SDLController("My Games");
    graphicsSetup = new OpenGLController();
    model = new Model();
    camera = new Camera(model);
    start = new Button("Start");
    racer = new Car();

	if(  !gameWindow->init() )
	{
		printf( "Failed to initialize SDL!\n" );
        return 0;
	}
	else
	{
        glutInit(&argc, argv);
        if(  !graphicsSetup->init() )
        {
            printf( "Failed to initialize openGL!\n" );
            return 0;
        }

		quit = false;

		SDL_Event event;

		SDL_StartTextInput();

		while( !quit )
		{
			while( SDL_PollEvent(&event) )
			{
				if( event.type == SDL_QUIT )
				{
					quit = true;
				}
				if( event.type == SDL_KEYDOWN )
				{
                    keyEvent(event.key.keysym.sym,
                                event.key.keysym.scancode);
				}
				if( event.type == SDL_WINDOWEVENT )
				{
                    windowEvent(event);
				}
                if ( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
                    //printf("Mouse moved to (%d,%d)\n", event.motion.x, event.motion.y);
                    mouseEvent(event);
                }
			}
            if(  !display() )
            {
                printf( "Failed to Disply Objects!\n" );
                return 0;
            }

			SDL_GL_SwapWindow( gameWindow->myWindow );
		}
		SDL_StopTextInput();
	}
    return 0;
}
