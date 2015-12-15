

#ifndef _SHARED_GRAPHICS_GL_CONTEXTGL_H_
#define _SHARED_GRAPHICS_GL_CONTEXTGL_H_ 

#include "context.h"

#include <SDL.h>
#define GL_GLEXT_PROTOTYPES

#include <GL/glew.h>
//#include <SDL_opengl.h>

#include "GL/GLU.h"
#include <string>
#include "font.h"

namespace Glest {

//

// =====================================================
//	class ContextGl
// =====================================================

class ContextGl: public Context{
protected:
	//PlatformContextGl pcgl;

public:
	virtual void init();
	virtual void end();
	virtual void reset(){};

	virtual void makeCurrent();
	virtual void swapBuffers();

	//const PlatformContextGl *getPlatformContextGl() const	{return &pcgl;}
};


}//end namespace

#endif
