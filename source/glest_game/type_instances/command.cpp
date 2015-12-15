

#include "command.h"

#include "command_type.h"

namespace Glest {

// =====================================================
// 	class Command
// =====================================================

Command::Command(const CommandType *ct, const Vec2i &pos){
    this->commandType= ct;  
    this->pos= pos;
	unitType= NULL;
} 

Command::Command(const CommandType *ct, Unit* unit){
    this->commandType= ct;  
    this->pos= Vec2i(0);
    this->unitRef= unit;
	unitType= NULL;
	if(unit!=NULL){
		unit->resetHighlight();
		pos= unit->getCellPos();
	}
} 

Command::Command(const CommandType *ct, const Vec2i &pos, const UnitType *unitType){
    this->commandType= ct;  
    this->pos= pos;
	this->unitType= unitType;
}

// =============== set ===============

void Command::setCommandType(const CommandType *commandType){
    this->commandType= commandType;
}

void Command::setPos(const Vec2i &pos){
     this->pos= pos;
}

void Command::setUnit(Unit *unit){
     this->unitRef= unit;
}

}//end namespace
