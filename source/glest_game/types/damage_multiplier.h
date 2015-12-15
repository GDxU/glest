

#ifndef _GLEST_GAME_DAMAGEMULTIPLIER_H_
#define _GLEST_GAME_DAMAGEMULTIPLIER_H_

#include <string>




namespace Glest {

// ===============================
// 	class AttackType  
// ===============================

class AttackType{
private:
	std::string name;
	int id;

public:
	int getId() const					{return id;}
	const std::string &getName() const		{return name;}

	void setName(const std::string &name)	{this->name= name;}
	void setId(int id)					{this->id= id;}
};

// ===============================
// 	class ArmorType  
// ===============================

class ArmorType{
private:
	std::string name;
	int id;

public:
	int getId() const					{return id;}
	const std::string &getName() const		{return name;}

	void setName(const std::string &name)	{this->name= name;}
	void setId(int id)					{this->id= id;}
};

// =====================================================
// 	class DamageMultiplierTable  
//
///	Some attack types have bonuses against some 
/// armor types and vice-versa
// =====================================================

class DamageMultiplierTable{
private:
	float *values;
	int attackTypeCount;
	int armorTypeCount;

public:
	DamageMultiplierTable();
	~DamageMultiplierTable();

	void init(int attackTypeCount, int armorTypeCount);
	float getDamageMultiplier(const AttackType *att, const ArmorType *art) const; 
	void setDamageMultiplier(const AttackType *att, const ArmorType *art, float value);
};

}//end namespace

#endif
