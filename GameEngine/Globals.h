#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Borra un puntero
#define RELEASE( x ) \
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Borra un array de punteros
#define RELEASE_ARRAY( x ) \
	{\
       if( x != nullptr )\
       {\
           delete[] x;\
	       x = nullptr;\
		 }\
	 }

// Configuración
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 253
#define SCREEN_SIZE 2
#define FULLSCREEN false
#define VSYNC true
#define TITLE "IAC's Game Engine"
#define DEBUG true

#endif //__GLOBALS_H__