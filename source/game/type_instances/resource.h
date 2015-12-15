
#ifndef _GLEST_GAME_RESOURCE_H_
#define _GLEST_GAME_RESOURCE_H_

#include <string>

#include "vec.h"




namespace Glest {



class ResourceType;

// =====================================================
// 	class Resource  
//
/// Amount of a given ResourceType
// =====================================================

class Resource{
private:
    int amount;
    const ResourceType *type;
	Vec2i pos;	
	int balance;

public: 
    void init(const ResourceType *rt, int amount);
    void init(const ResourceType *rt, const Vec2i &pos);

	int getAmount() const					{return amount;}
	const ResourceType * getType() const	{return type;}
	Vec2i getPos() const					{return pos;}
	int getBalance() const					{return balance;}
	std::string getDescription() const;

	void setAmount(int amount)				{this->amount= amount;}
	void setBalance(int balance)			{this->balance= balance;}

    bool decAmount(int i);
};

}// end namespace

#endif
