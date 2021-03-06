

#include "ai_interface.h"

#include "ai.h"
#include "command_type.h"
#include "faction.h"
#include "unit.h"
#include "unit_type.h"
#include "object.h"
#include "game.h"
#include "config.h"



// =====================================================
// 	class AiInterface
// =====================================================

namespace Glest {

AiInterface::AiInterface(Game &game, int factionIndex, int teamIndex){
	this->world= game.getWorld();
	this->commander= game.getCommander();
	this->console= game.getConsole();

	this->factionIndex= factionIndex;
	this->teamIndex= teamIndex;
	timer= 0;

	//init ai
	ai.init(this);

	//config
	logLevel= Config::getInstance().getInt("AiLog");
	redir= Config::getInstance().getBool("AiRedir");

	//clear log file
	if(logLevel>0){
		FILE *f= fopen(getLogFilename().c_str(), "wt");
		if(f==NULL){
            throw std::runtime_error("Can't open file: " + getLogFilename());
		}
		fprintf(f, "%s", "Glest AI log file\n\n");
		fclose(f);
	}
}

// ==================== main ==================== 

void AiInterface::update(){
	timer++;
	ai.update();
}

// ==================== misc ==================== 

void AiInterface::printLog(int logLevel, const std::string &s){
    if(this->logLevel>=logLevel){
		std::string logString= "(" + intToStr(factionIndex) + ") " + s;

		//print log to file
		FILE *f= fopen(getLogFilename().c_str(), "at");
		if(f==NULL){
            throw std::runtime_error("Can't open file: " + getLogFilename());
		}
		fprintf(f, "%s\n", logString.c_str());
		fclose(f);
		
		//redirect to console
		if(redir) {
			console->addLine(logString);
		}
    }
}

// ==================== interaction ==================== 

CommandResult AiInterface::giveCommand(int unitIndex, CommandClass commandClass, const Vec2i &pos){
    Command *c= new Command (world->getFaction(factionIndex)->getUnit(unitIndex)->getType()->getFirstCtOfClass(commandClass), pos);
	return world->getFaction(factionIndex)->getUnit(unitIndex)->giveCommand(c); 
}

CommandResult AiInterface::giveCommand(int unitIndex, const CommandType *commandType, const Vec2i &pos){
    return world->getFaction(factionIndex)->getUnit(unitIndex)->giveCommand(new Command(commandType, pos));
}

CommandResult AiInterface::giveCommand(int unitIndex, const CommandType *commandType, const Vec2i &pos, const UnitType *ut){
    return world->getFaction(factionIndex)->getUnit(unitIndex)->giveCommand(new Command(commandType, pos, ut));
}

CommandResult AiInterface::giveCommand(int unitIndex, const CommandType *commandType, Unit *u){
    return world->getFaction(factionIndex)->getUnit(unitIndex)->giveCommand(new Command(commandType, u));
}

// ==================== get data ====================  

int AiInterface::getMapMaxPlayers(){
     return world->getMaxPlayers();
}

Vec2i AiInterface::getHomeLocation(){
	return world->getMap()->getStartLocation(world->getFaction(factionIndex)->getStartLocationIndex());
}

Vec2i AiInterface::getStartLocation(int loactionIndex){
	return world->getMap()->getStartLocation(loactionIndex);
}

int AiInterface::getFactionCount(){
     return world->getFactionCount();
}

int AiInterface::getMyUnitCount() const{
	return world->getFaction(factionIndex)->getUnitCount();
}

int AiInterface::getMyUpgradeCount() const{
	return world->getFaction(factionIndex)->getUpgradeManager()->getUpgradeCount();
}

int AiInterface::onSightUnitCount(){
    int count=0;
	Map *map= world->getMap();
	for(int i=0; i<world->getFactionCount(); ++i){
		for(int j=0; j<world->getFaction(i)->getUnitCount(); ++j){
			SurfaceCell *sc= map->getSurfaceCell(Map::toSurfCoords(world->getFaction(i)->getUnit(j)->getPos()));
			if(sc->isVisible(teamIndex)){     
				count++;     
			}
		}	
	}
    return count;
}

const Resource *AiInterface::getResource(const ResourceType *rt){
	return world->getFaction(factionIndex)->getResource(rt);
}

const Unit *AiInterface::getMyUnit(int unitIndex){
    return world->getFaction(factionIndex)->getUnit(unitIndex);
}

const Unit *AiInterface::getOnSightUnit(int unitIndex){
     
    int count=0;
	Map *map= world->getMap();

	for(int i=0; i<world->getFactionCount(); ++i){
        for(int j=0; j<world->getFaction(i)->getUnitCount(); ++j){
            Unit *u= world->getFaction(i)->getUnit(j);
            if(map->getSurfaceCell(Map::toSurfCoords(u->getPos()))->isVisible(teamIndex)){
				if(count==unitIndex){
					return u;
				}
				else{
					count ++;
				}
            }
        }
	}
    return NULL;
}

const FactionType * AiInterface::getMyFactionType(){
	return world->getFaction(factionIndex)->getType();
}

const TechTree *AiInterface::getTechTree(){
	return world->getTechTree();
}

bool AiInterface::getNearestSightedResource(const ResourceType *rt, const Vec2i &pos, Vec2i &resultPos){
	float tmpDist;

	float nearestDist= infinity;
	bool anyResource= false;

	const Map *map= world->getMap();

	for(int i=0; i<map->getW(); ++i){
		for(int j=0; j<map->getH(); ++j){
			Vec2i surfPos= Map::toSurfCoords(Vec2i(i, j));
			
			//if explored cell
			if(map->getSurfaceCell(surfPos)->isExplored(teamIndex)){
				Resource *r= map->getSurfaceCell(surfPos)->getResource(); 
				
				//if resource cell
				if(r!=NULL && r->getType()==rt){
					tmpDist= pos.dist(Vec2i(i, j));
					if(tmpDist<nearestDist){
						anyResource= true;
						nearestDist= tmpDist;
						resultPos= Vec2i(i, j);
					}
				}
			}
		}
	}
	return anyResource;
}

bool AiInterface::isAlly(const Unit *unit) const{
	return world->getFaction(factionIndex)->isAlly(unit->getFaction());
}
bool AiInterface::reqsOk(const RequirableType *rt){
    return world->getFaction(factionIndex)->reqsOk(rt);
}

bool AiInterface::reqsOk(const CommandType *ct){
    return world->getFaction(factionIndex)->reqsOk(ct);
}

bool AiInterface::checkCosts(const ProducibleType *pt){
	return world->getFaction(factionIndex)->checkCosts(pt);
}

bool AiInterface::isFreeCells(const Vec2i &pos, int size, Field field){
    return world->getMap()->isFreeCells(pos, size, field);
}

}//end namespace
