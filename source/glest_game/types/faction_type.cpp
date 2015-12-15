

#include "faction_type.h"

#include "logger.h"
#include "util.h" 
#include "xml_parser.h"
#include "tech_tree.h"
#include "resource.h"
#include "platform_util.h"
#include "game_util.h"




namespace Glest {

// ======================================================
//          Class FactionType                   
// ======================================================

FactionType::FactionType(){
	music= NULL;	
}

//load a faction, given a directory
void FactionType::load(const std::string &dir, const TechTree *techTree, Checksum* checksum){

    name= lastDir(dir);

	Logger::getInstance().add("Faction type: "+ formatString(name), true);
    
	// a1) preload units
	std::string unitsPath= dir + "/units/*.";
    std::vector<std::string> unitFilenames;
    findAll(unitsPath, unitFilenames);
	unitTypes.resize(unitFilenames.size());
    for(int i=0; i<unitTypes.size(); ++i){
		std::string str= dir + "/units/" + unitFilenames[i];
		unitTypes[i].preLoad(str);
    }

	// a2) preload upgrades
	std::string upgradesPath= dir + "/upgrades/*.";
	std::vector<std::string> upgradeFilenames;
    findAll(upgradesPath, upgradeFilenames);
	upgradeTypes.resize(upgradeFilenames.size());
    for(int i=0; i<upgradeTypes.size(); ++i){
		std::string str= dir + "/upgrades/" + upgradeFilenames[i];
		upgradeTypes[i].preLoad(str);
    }
	
	// b1) load units
	try{
		for(int i=0; i<unitTypes.size(); ++i){
            std::string str= dir + "/units/" + unitTypes[i].getName();
            unitTypes[i].load(i, str, techTree, this, checksum);
        }
    }
    catch (const std::exception &e){
        throw std::runtime_error("Error loading units: " + dir + "\n" + e.what());
	}

	// b2) load upgrades
	try{
		for(int i=0; i<upgradeTypes.size(); ++i){
            std::string str= dir + "/upgrades/" + upgradeTypes[i].getName();
            upgradeTypes[i].load(str, techTree, this, checksum);
        }
    }
    catch (const std::exception &e){
        throw std::runtime_error("Error loading upgrades: " + dir + "\n" + e.what());
	}

	//open xml file
    std::string path= dir+"/"+name+".xml";

	checksum->addFile(path);

	XmlTree xmlTree;
	xmlTree.load(path);
	const XmlNode *factionNode= xmlTree.getRootNode();

	//read starting resources
	const XmlNode *startingResourcesNode= factionNode->getChild("starting-resources");

	startingResources.resize(startingResourcesNode->getChildCount());
	for(int i=0; i<startingResources.size(); ++i){
		const XmlNode *resourceNode= startingResourcesNode->getChild("resource", i);
		std::string name= resourceNode->getAttribute("name")->getRestrictedValue();
		int amount= resourceNode->getAttribute("amount")->getIntValue();
		startingResources[i].init(techTree->getResourceType(name), amount);
	}

	//read starting units
	const XmlNode *startingUnitsNode= factionNode->getChild("starting-units");
	for(int i=0; i<startingUnitsNode->getChildCount(); ++i){
		const XmlNode *unitNode= startingUnitsNode->getChild("unit", i);
		std::string name= unitNode->getAttribute("name")->getRestrictedValue();
		int amount= unitNode->getAttribute("amount")->getIntValue();
		startingUnits.push_back(PairPUnitTypeInt(getUnitType(name), amount)); 
	}

	//read music
	const XmlNode *musicNode= factionNode->getChild("music");
	bool value= musicNode->getAttribute("value")->getBoolValue();
	if(value){
		music= new StrSound();
		music->open(dir+"/"+musicNode->getAttribute("path")->getRestrictedValue());
	}
}

FactionType::~FactionType(){
	delete music;
}

// ==================== get ==================== 

const UnitType *FactionType::getUnitType(const std::string &name) const{     
    for(int i=0; i<unitTypes.size();i++){
		if(unitTypes[i].getName()==name){
            return &unitTypes[i];
		}
    }
    throw std::runtime_error("Unit not found: " + name);
}

const UpgradeType *FactionType::getUpgradeType(const std::string &name) const{     
    for(int i=0; i<upgradeTypes.size();i++){
		if(upgradeTypes[i].getName()==name){
            return &upgradeTypes[i];
		}
    }
    throw std::runtime_error("Upgrade not found: " + name);
}

int FactionType::getStartingResourceAmount(const ResourceType *resourceType) const{
	for(int i=0; i<startingResources.size(); ++i){
		if(startingResources[i].getType()==resourceType){
			return startingResources[i].getAmount();
		}
	}
	return 0;
}

}//end namespace
