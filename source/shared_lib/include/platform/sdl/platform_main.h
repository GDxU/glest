
#ifndef _SHARED_PLATFORM_MAIN_H_
#define _SHARED_PLATFORM_MAIN_H_

#include <SDL.h>
#include <iostream>
#include "SDL_main.h"

#define MAIN_FUNCTION(X) int main(int argc, char **argv)                     \
{                                                                            \
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)  {                                 \
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << "\n";  \
        return 1;                                                            \
    }                                                                        \
    int result = X(argc, argv);                                              \
    SDL_Quit();                                                              \
    return result;                                                           \
}

#endif
