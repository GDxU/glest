

#include "stats.h"


namespace Glest {

PlayerStats::PlayerStats(){
	victory= false;

	kills= 0;
	deaths= 0;
	unitsProduced= 0;
	resourcesHarvested= 0;
}

// =====================================================
// class Stats
// =====================================================

void Stats::init(int factionCount, int thisFactionIndex, const std::string& description){
	this->thisFactionIndex= thisFactionIndex;
	this->factionCount= factionCount;
	this->description= description;
}

void Stats::setVictorious(int playerIndex){
	playerStats[playerIndex].victory= true;
}

void Stats::kill(int killerFactionIndex, int killedFactionIndex){
	playerStats[killerFactionIndex].kills++;
	playerStats[killedFactionIndex].deaths++;
}

void Stats::produce(int producerFactionIndex){
	playerStats[producerFactionIndex].unitsProduced++;
}

void Stats::harvest(int harvesterFactionIndex, int amount){
	playerStats[harvesterFactionIndex].resourcesHarvested+= amount;
}

}//end namespace
