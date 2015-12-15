
#include "window_gl.h"

#include "context_gl.h"
#include "graphics_interface.h"



namespace Glest {

// =====================================================
//	class WindowGl
// =====================================================

void WindowGl::initGl(int colorBits, int depthBits, int stencilBits){
	context.setColorBits(colorBits);
	context.setDepthBits(depthBits);
	context.setStencilBits(stencilBits);
	
	context.init();
}

void WindowGl::makeCurrentGl() {
	GraphicsInterface::getInstance().setCurrentContext(&context);
	context.makeCurrent();
}

void WindowGl::swapBuffersGl(){
	context.swapBuffers();
}

}//end namespace
