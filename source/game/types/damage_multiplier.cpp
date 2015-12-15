

#include "damage_multiplier.h"


namespace Glest {

// =====================================================
// 	class DamageMultiplierTable
// =====================================================

DamageMultiplierTable::DamageMultiplierTable(){
	values= NULL;
}

DamageMultiplierTable::~DamageMultiplierTable(){
	delete [] values;
}

void DamageMultiplierTable::init(int attackTypeCount, int armorTypeCount){
	this->attackTypeCount= attackTypeCount;
	this->armorTypeCount= armorTypeCount;
	
	int valueCount= attackTypeCount*armorTypeCount;
	values= new float[valueCount];
	for(int i=0; i<valueCount; ++i){
		values[i]= 1.f;
	}
}

float DamageMultiplierTable::getDamageMultiplier(const AttackType *att, const ArmorType *art) const{
	return values[attackTypeCount*art->getId()+att->getId()];
}

void DamageMultiplierTable::setDamageMultiplier(const AttackType *att, const ArmorType *art, float value){
	values[attackTypeCount*art->getId()+att->getId()]= value;
}

}//end namespaces
