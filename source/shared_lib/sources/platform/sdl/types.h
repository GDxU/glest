
#ifndef _SHARED_PLATFORM_TYPES_H_
#define _SHARED_PLATFORM_TYPES_H_

#include <SDL_types.h>

namespace Glest {

// These don't have a real meaning in the SDL port
typedef void* WindowHandle;
typedef void* DeviceContextHandle;
typedef void* GlContextHandle;  	

typedef float float32;
typedef double float64;
// don't use Sint8 here because that is defined as signed char
// and some parts of the code do std::string str = (int8*) var;
typedef char int8;
typedef Uint8 uint8;
typedef Sint16 int16;
typedef Uint16 uint16;
typedef Sint32 int32;
typedef Uint32 uint32;
typedef Sint64 int64;

}//end namespace

#endif
