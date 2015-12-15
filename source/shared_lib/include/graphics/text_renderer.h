

#ifndef _SHARED_GRAPHICS_TEXTRENDERER_H_
#define _SHARED_GRAPHICS_TEXTRENDERER_H_

#include <string>

#include "vec.h"
#include "font.h"




namespace Glest {

// =====================================================
//	class TextRenderer2D
// =====================================================

class TextRenderer2D{
public:	
	virtual ~TextRenderer2D(){};

	virtual void begin(const Font2D *font)= 0;
	virtual void render(const std::string &text, int x, int y, bool centered= false)= 0;
	virtual void end()= 0;
};

// =====================================================
//	class TextRenderer3D
// =====================================================

class TextRenderer3D{
public:	
	virtual ~TextRenderer3D(){};

	virtual void begin(const Font3D *font)= 0;
	virtual void render(const std::string &text, float x, float y, float size, bool centered= false)= 0;
	virtual void end()= 0;
};

}//end namespace

#endif
