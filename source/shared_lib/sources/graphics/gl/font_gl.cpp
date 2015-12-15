

#include "font_gl.h"

#include "opengl.h"
#include "context_gl.h"

namespace Glest {



// =====================================================
//	class Font2DGl
// =====================================================

void Font2DGl::init(){
	assertGl();

	if(!inited){
		handle= glGenLists(charCount);
		createGlFontBitmaps(handle, type, size, width, charCount, metrics);
		inited= true;
	}

	assertGl();
}

void Font2DGl::end(){
	assertGl();

	if(inited){
		assert(glIsList(handle));
		glDeleteLists(handle, 1);
		inited= false;
	}

	assertGl();
}

// =====================================================
//	class Font3DGl
// =====================================================

void Font3DGl::init(){
	assertGl();

	if(!inited){
		handle= glGenLists(charCount);
		createGlFontOutlines(handle, type, width, depth, charCount, metrics);
		inited= true;
	}

	assertGl();
}

void Font3DGl::end(){
	assertGl();

	if(inited){
		assert(glIsList(handle));
		glDeleteLists(handle, 1);
	}

	assertGl();
}

}//end namespace
