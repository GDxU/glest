// ==============================================================
//	This file is part of Glest Shared Library (www.glest.org)
//
//	Copyright (C) 2001-2008 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#include "context_gl.h"

#include <cassert>
#include <stdexcept>

#include "opengl.h"
#include "sdl_private.h"
#include "opengl.h"
#include "sdl_private.h"
#include "noimpl.h"
#include "SDL.h"
#include <iostream>
#include <sstream>
#include <string>


static SDL_Window* s_window = NULL;

SDL_Window* getWindow() {
    return s_window;
}

namespace Glest {

// =====================================================
//	class ContextGl
// =====================================================

void ContextGl::init(){
	//pcgl.init(colorBits, depthBits, stencilBits);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // 	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 1);
    // 	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 1);
    // 	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 1);
    // 	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencilBits);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    int flags = SDL_WINDOW_OPENGL;
    if (Private::shouldBeFullscreen)
        flags |= SDL_WINDOW_FULLSCREEN;

    int resW = Private::ScreenWidth;
    int resH = Private::ScreenHeight;
    SDL_Window* screen = SDL_CreateWindow("Cocos2d SDL ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resW, resH, flags);
    //SDL_Surface* screen = SDL_SetVideoMode(resW, resH, colorBits, flags);

    SDL_GL_CreateContext(screen);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW init false";

    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
    {
        std::cout << "Ready for GLSL";
    }
    else
    {
        std::cout << "Not totally ready :(";
    }

    if (glewIsSupported("GL_VERSION_2_0"))
    {
        std::cout << "Ready for OpenGL 2.0";
    }
    else
    {
        std::cout << "OpenGL 2.0 not supported";
    }

    SDL_GL_SetSwapInterval(1);

    s_window = screen;

    if (screen == 0) {
        std::ostringstream msg;
        msg << "Couldn't set video mode "
            << resW << "x" << resH << " (" << colorBits
            << "bpp " << stencilBits << " stencil "
            << depthBits << " depth-buffer). SDL Error is: " << SDL_GetError();
        throw std::runtime_error(msg.str());
    }
}

void ContextGl::end(){
//	pcgl.end();
}

void ContextGl::makeCurrent(){
//	pcgl.makeCurrent();
}

void ContextGl::swapBuffers(){
	//pcgl.swapBuffers();
    SDL_GL_SwapWindow(s_window);

}

}//end namespace
