
#ifndef _GLEST_GAME_ELEMENTTYPE_H_ 
#define _GLEST_GAME_ELEMENTTYPE_H_

#include <vector>
#include <string>

#include "texture.h"
#include "resource.h"



namespace Glest {

class UpgradeType;
class TechTree;
class UnitType;
class UpgradeType;
class DisplayableType;
class ResourceType;

// =====================================================
// 	class DisplayableType
//
///	Base class for anything that has a name and a portrait
// =====================================================

class DisplayableType{
protected:
	std::string name;		//name
	Texture2D *image;	//portrait  

public:
	DisplayableType();
	virtual ~DisplayableType(){};

	//get
	std::string getName() const				{return name;}
	const Texture2D *getImage() const	{return image;}
};


// =====================================================
// 	class RequirableType  
//
///	Base class for anything that has requirements
// =====================================================

class RequirableType: public DisplayableType{
private:
	typedef std::vector<const UnitType*> UnitReqs;
	typedef std::vector<const UpgradeType*> UpgradeReqs;

protected:
	UnitReqs unitReqs;			//needed units
	UpgradeReqs upgradeReqs;	//needed upgrades

public:
	//get
	int getUpgradeReqCount() const						{return upgradeReqs.size();}
	int getUnitReqCount() const							{return unitReqs.size();}
	const UpgradeType *getUpgradeReq(int i) const		{return upgradeReqs[i];}
	const UnitType *getUnitReq(int i) const				{return unitReqs[i];}
    
    //other
    virtual std::string getReqDesc() const;
};


// =====================================================
// 	class ProducibleType  
//
///	Base class for anything that can be produced
// =====================================================

class ProducibleType: public RequirableType{
private:
	typedef std::vector<Resource> Costs;

protected:
	Costs costs;
    Texture2D *cancelImage;
	int productionTime;

public:
    ProducibleType();
	virtual ~ProducibleType();

    //get
	int getCostCount() const						{return costs.size();}
	const Resource *getCost(int i) const			{return &costs[i];}
	const Resource *getCost(const ResourceType *rt) const;
	int getProductionTime() const					{return productionTime;}
	const Texture2D *getCancelImage() const	{return cancelImage;}
            
    //varios
    void checkCostStrings(TechTree *techTree);
    
	virtual std::string getReqDesc() const;
};

}//end namespace

#endif
