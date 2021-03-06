

#ifndef _GLEST_GAME_FACTION_H_
#define _GLEST_GAME_FACTION_H_

#include <vector>
#include <map>

#include "upgrade.h"
#include "texture.h"
#include "resource.h"
#include "game_constants.h"








namespace Glest {

class Unit;
class TechTree;
class FactionType;
class ProducibleType;
class RequirableType;
class CommandType;
class UnitType;

// =====================================================
// 	class Faction
//
///	Each of the game players
// =====================================================

class Faction{
private:
    typedef std::vector<Resource> Resources;
    typedef std::vector<Resource> Store;
	typedef std::vector<Faction*> Allies;
	typedef std::vector<Unit*> Units;
    typedef std::map<int, Unit*> UnitMap;

private:
	UpgradeManager upgradeManager; 

    Resources resources;
    Store store;
	Allies allies;
	Units units;
	UnitMap unitMap;

    ControlType control;

	Texture2D *texture;
	const FactionType *factionType;

	int index;
	int teamIndex;
	int startLocationIndex;

	bool thisFaction;

public:
    void init(
		const FactionType *factionType, ControlType control, TechTree *techTree, 
		int factionIndex, int teamIndex, int startLocationIndex, bool thisFaction, bool giveResources);
	void end();

    //get
	const Resource *getResource(const ResourceType *rt) const;
	const Resource *getResource(int i) const			{return &resources[i];}
	int getStoreAmount(const ResourceType *rt) const;
	const FactionType *getType() const					{return factionType;}
	int getIndex() const								{return index;}
	int getTeam() const									{return teamIndex;}
	bool getCpuControl() const;
	bool getCpuUltraControl() const						{return control==ctCpuUltra;}
	Unit *getUnit(int i) const							{return units[i];}
	int getUnitCount() const							{return units.size();}		
	const UpgradeManager *getUpgradeManager() const		{return &upgradeManager;}
	const Texture2D *getTexture() const					{return texture;}
	int getStartLocationIndex() const					{return startLocationIndex;}

	//upgrades
	void startUpgrade(const UpgradeType *ut);
	void cancelUpgrade(const UpgradeType *ut);
	void finishUpgrade(const UpgradeType *ut);

	//cost application
	bool applyCosts(const ProducibleType *p);
	void applyDiscount(const ProducibleType *p, int discount);
	void applyStaticCosts(const ProducibleType *p);
	void applyStaticProduction(const ProducibleType *p);
	void deApplyCosts(const ProducibleType *p);
	void deApplyStaticCosts(const ProducibleType *p);
	void deApplyStaticConsumption(const ProducibleType *p);
	void applyCostsOnInterval();
	bool checkCosts(const ProducibleType *pt);

	//reqs
	bool reqsOk(const RequirableType *rt) const;
	bool reqsOk(const CommandType *ct) const;

	//diplomacy
	bool isAlly(const Faction *faction);

    //other
	Unit *findUnit(int id);
	void addUnit(Unit *unit);
	void removeUnit(Unit *unit);
	void addStore(const UnitType *unitType);
	void removeStore(const UnitType *unitType);

	//resources
	void incResourceAmount(const ResourceType *rt, int amount);
	void setResourceBalance(const ResourceType *rt, int balance);

private:
	void limitResourcesToStore();
	void resetResourceAmount(const ResourceType *rt);
};

}//end namespace

#endif
