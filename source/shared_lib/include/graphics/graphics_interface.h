

#ifndef _SHARED_GRAPHICS_GRAPHICSINTERFACE_H_
#define _SHARED_GRAPHICS_GRAPHICSINTERFACE_H_

namespace Glest {

class GraphicsFactory;
class Context;

// =====================================================
//	class GraphicsInterface  
//
///	Interface for the graphic engine
// =====================================================

class GraphicsInterface{
private:
	GraphicsFactory *graphicsFactory;
	Context *currentContext;

private:
	friend class TextureManager;
	friend class FontManager;

private:
	GraphicsInterface();
	GraphicsInterface(GraphicsInterface &);
	void operator=(GraphicsInterface &);

public:
	static GraphicsInterface &getInstance();

	void setFactory(GraphicsFactory *graphicsFactory);
	void setCurrentContext(Context *context);	

	Context *getCurrentContext() const		{return currentContext;}
	GraphicsFactory *getFactory() const		{return graphicsFactory;}
};

}//end namespace

#endif
