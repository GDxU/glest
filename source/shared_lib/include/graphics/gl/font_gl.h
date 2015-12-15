

#ifndef _SHARED_GRAPHICS_GL_FONTGL_H_
#define _SHARED_GRAPHICS_GL_FONTGL_H_

#include "font.h"
#include "opengl.h"

namespace Glest {

// =====================================================
//	class FontGl
// =====================================================

class FontGl{
protected:
	GLuint handle;

public:
	GLuint getHandle() const				{return handle;}
};

// =====================================================
//	class Font2DGl
//
///	OpenGL bitmap font
// =====================================================

class Font2DGl: public Font2D, public FontGl{
public:
	virtual void init();
	virtual void end();
};

// =====================================================
//	class Font3DGl
//
///	OpenGL outline font
// =====================================================

class Font3DGl: public Font3D, public FontGl{
public:
	virtual void init();
	virtual void end();
};

}//end namespace

#endif
