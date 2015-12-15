

#ifndef _GLEST_GAME_UPGRADE_H_
#define _GLEST_GAME_UPGRADE_H_

#include <vector>




namespace Glest {

class Unit;
class UpgradeType;

enum UpgradeState{
	usUpgrading, 
	usUpgraded,

	upgradeStateCount
};

class UpgradeManager;
class TotalUpgrade;

// =====================================================
// 	class Upgrade  
//
/// A bonus to an UnitType
// =====================================================

class Upgrade{
private:
	UpgradeState state;
	int factionIndex;
	const UpgradeType *type;

	friend class UpgradeManager;

public:
	Upgrade(const UpgradeType *upgradeType, int factionIndex);

private:
	//get
	UpgradeState getState() const;
	int getFactionIndex() const;
	const UpgradeType * getType() const;

	//set
	void setState(UpgradeState state);
};


// ===============================
// 	class UpgradeManager  
// ===============================

class UpgradeManager{
private:	
	typedef std::vector<Upgrade*> Upgrades;
	Upgrades upgrades;
public:
	~UpgradeManager();

	int getUpgradeCount() const		{return upgrades.size();}

	void startUpgrade(const UpgradeType *upgradeType, int factionIndex);
	void cancelUpgrade(const UpgradeType *upgradeType);
	void finishUpgrade(const UpgradeType *upgradeType);

	bool isUpgraded(const UpgradeType *upgradeType) const;
	bool isUpgrading(const UpgradeType *upgradeType) const;
	bool isUpgradingOrUpgraded(const UpgradeType *upgradeType) const;
	void computeTotalUpgrade(const Unit *unit, TotalUpgrade *totalUpgrade) const;
};

}//end namespace

#endif
