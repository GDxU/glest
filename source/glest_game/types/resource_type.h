

#ifndef _GLEST_GAME_RESOURCETYPE_H_
#define _GLEST_GAME_RESOURCETYPE_H_

#include "element_type.h"
#include "model.h"
#include "checksum.h"

namespace Glest {




enum ResourceClass{
	rcTech,		
	rcTileset,
	rcStatic,
	rcConsumable
};

// =====================================================
// 	class ResourceType
//
///	A type of resource that can be harvested or not
// =====================================================

class ResourceType: public DisplayableType{
private:
    ResourceClass resourceClass;
    int tilesetObject;	//used only if class==rcTileset
    int resourceNumber;	//used only if class==rcTech, resource number in the map
    int interval;		//used only if class==rcConsumable
	int defResPerPatch;	//used only if class==rcTileset || class==rcTech
    Model *model;

public:
    void load(const std::string &dir, Checksum* checksum);

    //get
	int getClass() const			{return resourceClass;}
	int getTilesetObject() const	{return tilesetObject;}
	int getResourceNumber() const	{return resourceNumber;}
	int getInterval() const			{return interval;}
	int getDefResPerPatch() const	{return defResPerPatch;}
	const Model *getModel() const	{return model;}

	static ResourceClass strToRc(const std::string &s);
};

} //end namespace

#endif
