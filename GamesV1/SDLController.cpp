#include "SDLController.h"

SDLController::SDLController(char* title){
    Game_Title = title;
    myWindow = NULL;
    Flag = SDL_WINDOW_SHOWN;
}

SDLController::~SDLController(){
    SDL_GL_DeleteContext(myContext); // Delete our opengl context
    SDL_DestroyWindow(myWindow); // Close and destroy the window
    SDL_Quit(); // Clean up
}

bool SDLController::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
        /* Request opengl 3.2 context.
         * SDL doesn't have the ability to choose which profile at this time of writing,
         * but it should default to the core profile */
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        /* Turn on double buffering with a 24bit Z buffer.
         * You may need to change this to 16 or 32 for your system */
        //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		myWindow = SDL_CreateWindow( Game_Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | Flag );
		if( myWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
        SDL_version compiled;
        SDL_version linked;

        SDL_VERSION(&compiled);
        SDL_GetVersion(&linked);
        printf("We compiled against SDL version %d.%d.%d ...\n",
               compiled.major, compiled.minor, compiled.patch);
        printf("But we are linking against SDL version %d.%d.%d.\n",
               linked.major, linked.minor, linked.patch);
        if (! SDL_VERSION_ATLEAST(2,0,0)) {
            printf("SDL_VERSION %i is less than 2.0.0", SDL_MAJOR_VERSION);
            return 1;
        }
        SDL_VERSION(&info.version); // initialize info structure with SDL version info

          if(SDL_GetWindowWMInfo(myWindow,&info)) { // the call returns true on success
            // success
            const char *subsystem = "an unknown system!";
            switch(info.subsystem) {
              case SDL_SYSWM_UNKNOWN:   break;
              case SDL_SYSWM_WINDOWS:   subsystem = "Microsoft Windows(TM)";  break;
              case SDL_SYSWM_X11:       subsystem = "X Window System";        break;
        #if SDL_VERSION_ATLEAST(2, 0, 3)
              case SDL_SYSWM_WINRT:     subsystem = "WinRT";                  break;
        #endif
              case SDL_SYSWM_DIRECTFB:  subsystem = "DirectFB";               break;
              case SDL_SYSWM_COCOA:     subsystem = "Apple OS X";             break;
              case SDL_SYSWM_UIKIT:     subsystem = "UIKit";                  break;
        #if SDL_VERSION_ATLEAST(2, 0, 2)
              case SDL_SYSWM_WAYLAND:   subsystem = "Wayland";                break;
              case SDL_SYSWM_MIR:       subsystem = "Mir";                    break;
        #endif
        #if SDL_VERSION_ATLEAST(2, 0, 4)
              case SDL_SYSWM_ANDROID:   subsystem = "Android";                break;
        #endif
            }

            printf("This program is running SDL version %d.%d.%d on %s\n",
                (int)info.version.major,
                (int)info.version.minor,
                (int)info.version.patch,
                subsystem);
          } else {
            // call failed
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't get window information: %s\n", SDL_GetError());
          }
		myContext = SDL_GL_CreateContext(myWindow);  /* Create our opengl context and attach it to our window */

        SDL_GL_SetSwapInterval(1);  /* This makes our buffer swap syncronized with the monitor's vertical refresh */
	}
	return success;
}

int SDLController::getWidth(){
    return SCREEN_WIDTH;
}

int SDLController::getHeight(){
    return SCREEN_WIDTH;
}

void SDLController::setFlag(int a){
    switch (a) {
        case 5:
          Flag = SDL_WINDOW_FULLSCREEN;
            printf( "SDL_SCANCODE_F key Event Catch!\n" );
          break;
        case 4101:
          Flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
          break;
        default:
          // Code
          break;
    }
}


/*
SDL_WINDOW_FULLSCREEN // ID:5  fullscreen window
SDL_WINDOW_FULLSCREEN_DESKTOP // ID:4101  fullscreen window at the current desktop resolution
SDL_WINDOW_OPENGL // ID:6  window usable with OpenGL context
SDL_WINDOW_SHOWN // ID:4  window is visible
SDL_WINDOW_HIDDEN // ID:8  window is not visible
SDL_WINDOW_BORDERLESS // ID:20  no window decoration
SDL_WINDOW_RESIZABLE // ID:36  window can be resized
SDL_WINDOW_MINIMIZED // ID:4  window is minimized
SDL_WINDOW_MAXIMIZED // ID:132  window is maximized
SDL_WINDOW_INPUT_GRABBED // ID:260  window has grabbed input focus
SDL_WINDOW_INPUT_FOCUS // ID:4  window has input focus
SDL_WINDOW_MOUSE_FOCUS // ID:4  window has mouse focus
SDL_WINDOW_FOREIGN // ID:4  window not created by SDL
SDL_WINDOW_ALLOW_HIGHDPI // ID:8196  window should be created in high-DPI mode if supported (>= SDL 2.0.1)
SDL_WINDOW_MOUSE_CAPTURE // ID:5  window has mouse captured (unrelated to INPUT_GRABBED, >= SDL 2.0.4)
*/

