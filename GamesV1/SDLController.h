#ifndef SDLCONTROLLER_H
#define SDLCONTROLLER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

class SDLController {
	public:
        SDL_Window* myWindow; /* Our window handle */
        SDL_SysWMinfo info;
        SDL_GLContext myContext; /* Our opengl context handle */
		SDLController(char* title);
		~SDLController();
        bool init();
        void setFlag(int a);
        int getWidth();
        int getHeight();
        Uint32 Flag;

    private:
        char* Game_Title;
        int SCREEN_WIDTH = 800;
        int SCREEN_HEIGHT = 600;
        int SCREEN_FPS = 60;
};


#endif
