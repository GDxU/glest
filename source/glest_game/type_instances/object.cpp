

#include "object.h"

#include "faction_type.h"
#include "tech_tree.h"
#include "resource.h"
#include "upgrade.h"
#include "object_type.h"
#include "resource.h"
#include "util.h"
#include "random.h"



namespace Glest {


// =====================================================
// 	class Object
// =====================================================

Object::Object(ObjectType *objectType, const Vec3f &pos){
	Random random;

	random.init(static_cast<int>(pos.x*pos.z));

	this->objectType= objectType;
	resource= NULL;
	this->pos= pos + Vec3f(random.randRange(-0.6f, 0.6f), 0.0f, random.randRange(-0.6f, 0.6f));
	rotation= random.randRange(0.f, 360.f);
	if(objectType!=NULL){
		variation = random.randRange(0, objectType->getModelCount()-1);
	}
}

Object::~Object(){
	delete resource; 
}

const Model *Object::getModel() const{
	return objectType==NULL? resource->getType()->getModel(): objectType->getModel(variation);
}

bool Object::getWalkable() const{
	return objectType==NULL? false: objectType->getWalkable();
}

void Object::setResource(const ResourceType *resourceType, const Vec2i &pos){
	resource= new Resource();
	resource->init(resourceType, pos);
}

}//end namespace
