

#include "graphics_interface.h"

#include <cstddef>



namespace Glest {

// =====================================================
//	class GraphicsInterface
// =====================================================

GraphicsInterface::GraphicsInterface(){
	graphicsFactory= NULL;
}

GraphicsInterface &GraphicsInterface::getInstance(){
	static GraphicsInterface graphicsInterface;
	return graphicsInterface;
}

void GraphicsInterface::setFactory(GraphicsFactory *graphicsFactory){
	this->graphicsFactory= graphicsFactory;
}

}//end namespace
