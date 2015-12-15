
#ifndef _GLEST_GAME_OBJECTTYPE_H_
#define _GLEST_GAME_OBJECTTYPE_H_

#include <vector>

#include "model.h"
#include "vec.h"




namespace Glest {




// =====================================================
// 	class ObjectType  
//
///	Each of the possible objects of the map: trees, stones ...
// =====================================================

class ObjectType{
private:
	typedef std::vector<Model*> Models;

private:
	static const int tree1= 0;
	static const int tree2= 1;
	static const int choppedTree= 2;

private:
	Models models;
	Vec3f color;
	int objectClass;
	bool walkable;

public:
	void init(int modelCount, int objectClass, bool walkable);

	void loadModel(const std::string &path);

	Model *getModel(int i)			{return models[i];}
	int getModelCount() const		{return models.size();}
	const Vec3f &getColor() const	{return color;} 
	int getClass() const			{return objectClass;}
	bool getWalkable() const		{return walkable;}
	bool isATree() const			{return objectClass==tree1 || objectClass==tree2;}
};

}//end namespace

#endif
