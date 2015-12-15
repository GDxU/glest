

#ifndef _SHARED_GRAPHICS_GL_TEXTRENDERERGL_H_
#define _SHARED_GRAPHICS_GL_TEXTRENDERERGL_H_

#include "text_renderer.h"

namespace Glest {

class Font2DGl;
class Font3DGl;

// =====================================================
//	class TextRenderer2DGl
// =====================================================

class TextRenderer2DGl: public TextRenderer2D{
private:
	const Font2DGl *font;
	bool rendering;

public:
	TextRenderer2DGl();

	virtual void begin(const Font2D *font);
	virtual void render(const std::string &text, int x, int y, bool centered);
	virtual void end();
};

// =====================================================
//	class TextRenderer3DGl
// =====================================================

class TextRenderer3DGl: public TextRenderer3D{
private:
	const Font3DGl *font;
	bool rendering;

public:
	TextRenderer3DGl();

	virtual void begin(const Font3D *font);
	virtual void render(const std::string &text, float x, float y, float size, bool centered);
	virtual void end();
};

}//end namespace

#endif
