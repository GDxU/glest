

#include "element_type.h"

#include <cassert>

#include "resource_type.h" 
#include "upgrade_type.h"
#include "unit_type.h"
#include "resource.h"
#include "tech_tree.h"
#include "logger.h"
#include "lang.h"
#include "renderer.h"



namespace Glest {

// =====================================================
// 	class DisplayableType
// =====================================================

DisplayableType::DisplayableType(){
	image= NULL;
}

// =====================================================
// 	class RequirableType
// =====================================================

std::string RequirableType::getReqDesc() const{
	bool anyReqs= false;

	std::string reqString;
	for(int i=0; i<getUnitReqCount(); ++i){
        reqString+= getUnitReq(i)->getName();
        reqString+= "\n";
		anyReqs= true;
    }

    for(int i=0; i<getUpgradeReqCount(); ++i){
        reqString+= getUpgradeReq(i)->getName();
        reqString+= "\n";
		anyReqs= true;
    }

	std::string str= getName();
	if(anyReqs){
		return str + " " + Lang::getInstance().get("Reqs") + ":\n" + reqString;
	}
	else{
		return str;
	}
}  

// =====================================================
// 	class ProducibleType
// =====================================================

ProducibleType::ProducibleType(){
	cancelImage= NULL;
}

ProducibleType::~ProducibleType(){
}

const Resource *ProducibleType::getCost(const ResourceType *rt) const{
	for(int i=0; i<costs.size(); ++i){
		if(costs[i].getType()==rt){
			return &costs[i];
		}
	}
	return NULL;
}

std::string ProducibleType::getReqDesc() const{
    std::string str= getName()+" "+Lang::getInstance().get("Reqs")+":\n";
    for(int i=0; i<getCostCount(); ++i){
        if(getCost(i)->getAmount()!=0){
            str+= getCost(i)->getType()->getName();
            str+= ": "+ intToStr(getCost(i)->getAmount());
            str+= "\n";
        }
    }

    for(int i=0; i<getUnitReqCount(); ++i){
        str+= getUnitReq(i)->getName();
        str+= "\n";
    }

    for(int i=0; i<getUpgradeReqCount(); ++i){
        str+= getUpgradeReq(i)->getName();
        str+= "\n";
    }

    return str;
}   

}//end namespace
