

#ifndef _SHARED_PLATFORM_WINDOWGL_H_
#define _SHARED_PLATFORM_WINDOWGL_H_

#include "context_gl.h"
#include "window.h"



namespace Glest {

// =====================================================
//	class WindowGl
// =====================================================

class WindowGl: public Window{
private:
	ContextGl context;

public:
	void initGl(int colorBits, int depthBits, int stencilBits);
	void makeCurrentGl();
	void swapBuffersGl();
};

}//end namespace

#endif
