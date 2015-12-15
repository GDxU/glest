

#ifndef _GLEST_GAME_FACTIONTYPE_H_
#define _GLEST_GAME_FACTIONTYPE_H_

#include "unit_type.h"
#include "upgrade_type.h"
#include "sound.h"



namespace Glest {

// =====================================================
// 	class FactionType
//
///	Each of the possible factions the user can select
// =====================================================

class FactionType{
private:
    typedef std::pair<const UnitType*, int> PairPUnitTypeInt;
	typedef std::vector<UnitType> UnitTypes; 
	typedef std::vector<UpgradeType> UpgradeTypes;
	typedef std::vector<PairPUnitTypeInt> StartingUnits;
	typedef std::vector<Resource> Resources;

private:
    std::string name;
    UnitTypes unitTypes;
    UpgradeTypes upgradeTypes;
	StartingUnits startingUnits;
	Resources startingResources;
	StrSound *music;

public:
	//init
	FactionType();
    void load(const std::string &dir, const TechTree *techTree, Checksum* checksum);
	~FactionType();

    //get
	int getUnitTypeCount() const						{return unitTypes.size();}
	int getUpgradeTypeCount() const						{return upgradeTypes.size();}
	std::string getName() const								{return name;}
	const UnitType *getUnitType(int i) const			{return &unitTypes[i];}
	const UpgradeType *getUpgradeType(int i) const		{return &upgradeTypes[i];}
	StrSound *getMusic() const							{return music;}
	int getStartingUnitCount() const					{return startingUnits.size();}
	const UnitType *getStartingUnit(int i) const		{return startingUnits[i].first;}
	int getStartingUnitAmount(int i) const				{return startingUnits[i].second;}
	
	const UnitType *getUnitType(const std::string &name) const;  
	const UpgradeType *getUpgradeType(const std::string &name) const;  
	int getStartingResourceAmount(const ResourceType *resourceType) const;
};

}//end namespace

#endif
