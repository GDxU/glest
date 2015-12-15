

#ifndef _GLEST_GAME_TECHTREE_H_
#define _GLEST_GAME_TECHTREE_H_

#include "util.h"
#include "resource_type.h"
#include "faction_type.h"
#include "damage_multiplier.h"

namespace Glest {

// =====================================================
// 	class TechTree
//
///	A set of factions and resources
// =====================================================

class TechTree{
private:
	typedef std::vector<ResourceType> ResourceTypes;
	typedef std::vector<FactionType> FactionTypes;
	typedef std::vector<ArmorType> ArmorTypes;
	typedef std::vector<AttackType> AttackTypes;

private:
    std::string desc;
    ResourceTypes resourceTypes;
    FactionTypes factionTypes;
	ArmorTypes armorTypes;
	AttackTypes attackTypes;
	DamageMultiplierTable damageMultiplierTable;

public:
    void load(const std::string &dir, Checksum* checksum);
    ~TechTree();
    
    //get
	int getResourceTypeCount() const							{return resourceTypes.size();}
	int getTypeCount() const									{return factionTypes.size();}
	const FactionType *getType(int i) const						{return &factionTypes[i];}
	const ResourceType *getResourceType(int i) const			{return &resourceTypes[i];}
    const std::string &getDesc() const								{return desc;}
	const FactionType *getType(const std::string &name) const;
	const ResourceType *getResourceType(const std::string &name) const;
    const ResourceType *getTechResourceType(int i) const;
    const ResourceType *getFirstTechResourceType() const;
	const ArmorType *getArmorType(const std::string &name) const;
	const AttackType *getAttackType(const std::string &name) const;
	float getDamageMultiplier(const AttackType *att, const ArmorType *art) const;
};

} //end namespace

#endif
