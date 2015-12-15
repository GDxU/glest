// ==============================================================
//	This file is part of Glest (www.glest.org)
//
//	Copyright (C) 2001-2008 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

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
