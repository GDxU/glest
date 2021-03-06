

#ifndef _GLEST_GAME_UPGRADETYPE_H_
#define _GLEST_GAME_UPGRADETYPE_H_


#include "element_type.h"
#include "checksum.h"

namespace Glest {

class TechTree;
class FactionType;
class UnitType;

// ===============================
// 	class UpgradeTypeBase 
// ===============================

class UpgradeTypeBase{
protected:
    int maxHp;
    int sight;
    int maxEp;
    int armor;
    int attackStrength;
    int attackRange;
    int moveSpeed;
    int prodSpeed;    

public:
	int getMaxHp() const			{return maxHp;}
	int getSight() const			{return sight;}
	int getMaxEp() const			{return maxEp;}
	int getArmor() const			{return armor;}
	int getAttackStrength() const	{return attackStrength;}
	int getAttackRange() const		{return attackRange;}
	int getMoveSpeed() const		{return moveSpeed;}
	int getProdSpeed() const		{return prodSpeed;}
};

// ===============================
// 	class UpgradeType  
// ===============================

class UpgradeType: public UpgradeTypeBase, public ProducibleType{
private:
    std::vector<const UnitType*> effects; 
    
public:
	void preLoad(const std::string &dir);
    void load(const std::string &dir, const TechTree *techTree, const FactionType *factionType, Checksum* checksum);

    //get all
	int getEffectCount() const				{return effects.size();}
	const UnitType * getEffect(int i) const	{return effects[i];}
	bool isAffected(const UnitType *unitType) const; 

    //other methods
	virtual std::string getReqDesc() const;
};

// ===============================
// 	class TotalUpgrade  
// ===============================

class TotalUpgrade: public UpgradeTypeBase{
public:
	TotalUpgrade();

	void reset();
	void sum(const UpgradeType *ut); 
	void incLevel(const UnitType *ut);
};

}//end namespace

#endif
