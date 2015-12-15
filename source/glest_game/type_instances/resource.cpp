

#include "resource.h"

#include "conversion.h"
#include "resource_type.h"




namespace Glest {

// =====================================================
// 	class Resource
// =====================================================

void Resource::init(const ResourceType *rt, int amount){
    this->type= rt;
    this->amount= amount;        
	pos= Vec2i(0);
	balance= 0;
}

void Resource::init(const ResourceType *rt, const Vec2i &pos){
	this->type=rt;
	amount=rt->getDefResPerPatch();
	this->pos= pos;
}

std::string Resource::getDescription() const{
     std::string str;

     str+= type->getName();
     str+="\n";
     str+= intToStr(amount);
     str+="/";
     str+= intToStr(type->getDefResPerPatch());

     return str;
}

bool Resource::decAmount(int i){
     amount-= i;
     if(amount>0)
          return false;
     return true;
}

}//end namespace
