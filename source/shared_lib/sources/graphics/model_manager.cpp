

#include "model_manager.h"

#include "graphics_interface.h"
#include "graphics_factory.h"

namespace Glest {

// =====================================================
//	class ModelManager
// =====================================================

ModelManager::ModelManager(){
	textureManager= NULL;
}

ModelManager::~ModelManager(){
	end();
}

Model *ModelManager::newModel(){
	Model *model= GraphicsInterface::getInstance().getFactory()->newModel();
	model->setTextureManager(textureManager);
	models.push_back(model);
	return model;
}

void ModelManager::init(){
	for(size_t i=0; i<models.size(); ++i){
		models[i]->init();
	}
} 

void ModelManager::end(){
	for(size_t i=0; i<models.size(); ++i){
		models[i]->end();
		delete models[i];
	}
	models.clear();
}


}//end namespace
