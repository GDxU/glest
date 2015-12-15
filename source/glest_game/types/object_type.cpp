

#include "object_type.h"

#include "renderer.h"

namespace Glest {

// =====================================================
// 	class ObjectType
// =====================================================

void ObjectType::init(int modelCount, int objectClass, bool walkable){
	models.reserve(modelCount);
	this->objectClass= objectClass;
	this->walkable= walkable;
}

void ObjectType::loadModel(const std::string &path){
	Model *model= Renderer::getInstance().newModel(rsGame);
	model->load(path);
	color= Vec3f(0.f);
	if(model->getMeshCount()>0 && model->getMesh(0)->getTexture(0)!=NULL){
		const Pixmap2D *p= model->getMesh(0)->getTexture(0)->getPixmap();
		color= p->getPixel3f(p->getW()/2, p->getH()/2);
	}
	models.push_back(model);
}

}//end namespace
