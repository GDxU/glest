
#ifndef _GLEST_GAME_OBJECT_H_
#define _GLEST_GAME_OBJECT_H_

#include "model.h"
#include "vec.h"

namespace Glest {

class ObjectType;
class ResourceType;
class Resource;





// =====================================================
// 	class Object
//
///	A map object: tree, stone...
// =====================================================

class Object{
private:
	ObjectType *objectType;
	Resource *resource;
	Vec3f pos;
	float rotation;
	int variation;

public:
	Object(ObjectType *objectType, const Vec3f &pos);
	~Object();

	void setHeight(float height)		{pos.y= height;}
	
	const ObjectType *getType() const	{return objectType;}
	Resource *getResource() const		{return resource;}
	Vec3f getPos() const				{return pos;}
	float getRotation()					{return rotation;}	
	const Model *getModel() const;
	bool getWalkable() const;

	void setResource(const ResourceType *resourceType, const Vec2i &pos);
};

}//end namespace

#endif
