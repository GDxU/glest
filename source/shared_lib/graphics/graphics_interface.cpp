

#include "graphics_interface.h"

#include <cstddef>

#include "context.h"


namespace Glest {

// =====================================================
//	class GraphicsInterface
// =====================================================

GraphicsInterface::GraphicsInterface(){
	graphicsFactory= NULL;
	currentContext= NULL;
}

GraphicsInterface &GraphicsInterface::getInstance(){
	static GraphicsInterface graphicsInterface;
	return graphicsInterface;
}

void GraphicsInterface::setFactory(GraphicsFactory *graphicsFactory){
	this->graphicsFactory= graphicsFactory;
}

void GraphicsInterface::setCurrentContext(Context *context){
	this->currentContext= context;
	currentContext->makeCurrent();
}

}//end namespace
