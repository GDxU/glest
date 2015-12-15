

#include "lang.h"

#include <stdexcept>

#include "logger.h"
#include "util.h"



namespace Glest {

// =====================================================
// 	class Lang
// =====================================================

Lang &Lang::getInstance(){
	static Lang lang;
	return lang;
} 

void Lang::loadStrings(const std::string &language){
	this->language= language;
	strings.clear();
	strings.load("data/lang/"+language+".lng");
}

void Lang::loadScenarioStrings(const std::string &scenarioDir, const std::string &scenarioName){
	std::string path= scenarioDir + "/" + scenarioName + "/" + scenarioName + "_" + language + ".lng";
	
	scenarioStrings.clear();
	
	//try to load the current language first
	if(fileExists(path)){
		scenarioStrings.load(path);
	}
	else{
		//try english otherwise
		std::string path= scenarioDir + "/" +scenarioName + "/" + scenarioName + "_english.lng";
		if(fileExists(path)){
			scenarioStrings.load(path);
		}
	}
}

std::string Lang::get(const std::string &s){
	try{
		return strings.getString(s);
	}
	catch(std::exception &){
		return "???" + s + "???";
	}
}

std::string Lang::getScenarioString(const std::string &s){
	try{
		return scenarioStrings.getString(s);
	}
    catch (std::exception &){
		return "???" + s + "???";
	}
}

}//end namespace
