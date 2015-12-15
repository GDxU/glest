

#ifndef _SHARED_GRAPHICS_MODELMANAGER_H_
#define _SHARED_GRAPHICS_MODELMANAGER_H_

#include "model.h"

#include <vector>




namespace Glest {

class TextureManager;

// =====================================================
//	class ModelManager
// =====================================================

class ModelManager{
protected:
	typedef std::vector<Model*> ModelContainer;

protected:
	ModelContainer models;
	TextureManager *textureManager;

public:
	ModelManager();
	virtual ~ModelManager();

	Model *newModel();

	void init();
	void end();

	void setTextureManager(TextureManager *textureManager)	{this->textureManager= textureManager;}
};

}//end namespace

#endif
