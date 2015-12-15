

#ifndef _SHARED_GRAPHICS_FONTMANAGER_H_
#define _SHARED_GRAPHICS_FONTMANAGER_H_

#include "font.h"

#include <vector>




namespace Glest {

// =====================================================
//	class FontManager
//
///	Creates, Intializes, Finalizes, and Deletes fonts
// =====================================================

class FontManager{
protected:
	typedef std::vector<Font*> FontContainer;

protected:
	FontContainer fonts;

public:
	virtual ~FontManager();

	Font2D *newFont2D();
	Font3D *newFont3D();

	void init();
	void end();
};

}//end namespace

#endif
