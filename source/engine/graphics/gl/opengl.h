

#ifndef _SHARED_GRAPHICS_GL_OPENGL_H_
#define _SHARED_GRAPHICS_GL_OPENGL_H_

#include <cassert>
#include <stdexcept>
#include <string>

#include "conversion.h"
#include "context_gl.h"






namespace Glest {



// =====================================================
//	Globals
// =====================================================

bool isGlExtensionSupported(const char *extensionName);
bool isGlVersionSupported(int major, int minor, int release);
const char *getGlVersion();
const char *getGlRenderer();
const char *getGlVendor();
const char *getGlExtensions();
const char *getGlPlatformExtensions();
int getGlMaxLights();
int getGlMaxTextureSize();
int getGlMaxTextureUnits();
int getGlModelviewMatrixStackDepth();
int getGlProjectionMatrixStackDepth();
void checkGlExtension(const char *extensionName);

void inline _assertGl(const char *file, int line){

	GLenum error= glGetError();

	if(error != GL_NO_ERROR){
		const char *errorString= reinterpret_cast<const char*>(gluErrorString(error));
        throw std::runtime_error("OpenGL error: " + std::string(errorString) + " at file: " + std::string(file) + ", line " + intToStr(line));
	}

}

#ifdef NDEBUG
#define assertGl() ((void) 0);

#else

#define assertGl() _assertGl(__FILE__, __LINE__);
	
#endif

}//end namespace

#endif
