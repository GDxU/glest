
#ifndef _SHARED_PLATFORM_SDL_GLOBALS_H_
#define _SHARED_PLATFORM_SDL_GLOBALS_H_

// This header contains things that should not be used outside the platform/sdl
// directory

namespace Glest {
    namespace Private {
        extern bool shouldBeFullscreen;
        extern int ScreenWidth;
        extern int ScreenHeight;
    }
}

#endif

