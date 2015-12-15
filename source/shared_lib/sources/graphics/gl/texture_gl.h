

#ifndef _SHARED_GRAPHICS_GL_TEXTUREGL_H_
#define _SHARED_GRAPHICS_GL_TEXTUREGL_H_

#include "texture.h"
#include "opengl.h"

namespace Glest {

// =====================================================
//	class TextureGl
// =====================================================

class TextureGl{
protected:
	GLuint handle;	

public:
	GLuint getHandle() const	{return handle;}
};

// =====================================================
//	class Texture1DGl
// =====================================================

class Texture1DGl: public Texture1D, public TextureGl{
public:
	virtual void init(Filter filter, int maxAnisotropy= 1);
	virtual void end();
};

// =====================================================
//	class Texture2DGl
// =====================================================

class Texture2DGl: public Texture2D, public TextureGl{
public:
	virtual void init(Filter filter, int maxAnisotropy= 1);
	virtual void end();
};

// =====================================================
//	class Texture3DGl
// =====================================================

class Texture3DGl: public Texture3D, public TextureGl{
public:
	virtual void init(Filter filter, int maxAnisotropy= 1);
	virtual void end();
};

// =====================================================
//	class TextureCubeGl
// =====================================================

class TextureCubeGl: public TextureCube, public TextureGl{
public:
	virtual void init(Filter filter, int maxAnisotropy= 1);
	virtual void end();
};

}//end namespace

#endif
