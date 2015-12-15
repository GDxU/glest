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

#ifndef _GLEST_GAME_GAMESETTINGS_H_
#define _GLEST_GAME_GAMESETTINGS_H_

#include "game_constants.h"

namespace Glest {

// =====================================================
//	class GameSettings
// =====================================================

class GameSettings{
private:
	std::string description;
	std::string map;
	std::string tileset;
	std::string tech;
	std::string scenario;
	std::string scenarioDir;
	std::string factionTypeNames[GameConstants::maxPlayers]; //faction names

	ControlType factionControls[GameConstants::maxPlayers];

	int thisFactionIndex;
	int factionCount;
	int teams[GameConstants::maxPlayers];
	int startLocationIndex[GameConstants::maxPlayers];

	bool defaultUnits;
	bool defaultResources;
	bool defaultVictoryConditions;

public:	
	//get
	const std::string &getDescription() const						{return description;}
	const std::string &getMap() const 								{return map;}
	const std::string &getTileset() const							{return tileset;}
	const std::string &getTech() const								{return tech;}
	const std::string &getScenario() const							{return scenario;}
	const std::string &getScenarioDir() const						{return scenarioDir;}
	const std::string &getFactionTypeName(int factionIndex) const	{return factionTypeNames[factionIndex];}
	ControlType getFactionControl(int factionIndex) const		{return factionControls[factionIndex];}

	int getThisFactionIndex() const						{return thisFactionIndex;}
	int getFactionCount() const							{return factionCount;} 
	int getTeam(int factionIndex) const					{return teams[factionIndex];}
	int getStartLocationIndex(int factionIndex) const	{return startLocationIndex[factionIndex];}

	bool getDefaultUnits() const				{return defaultUnits;}
	bool getDefaultResources() const			{return defaultResources;}
	bool getDefaultVictoryConditions() const	{return defaultVictoryConditions;}

	//set
    void setDescription(const std::string& description)						{ this->description = description; }
    void setMap(const std::string& map)										{ this->map = map; }
    void setTileset(const std::string& tileset)								{ this->tileset = tileset; }
    void setTech(const std::string& tech)									{ this->tech = tech; }
    void setScenario(const std::string& scenario)							{ this->scenario = scenario; }
    void setScenarioDir(const std::string& scenarioDir)						{ this->scenarioDir = scenarioDir; }

    void setFactionTypeName(int factionIndex, const std::string& factionTypeName)	{ this->factionTypeNames[factionIndex] = factionTypeName; }

	void setFactionControl(int factionIndex, ControlType controller)			{this->factionControls[factionIndex]= controller;}

	void setThisFactionIndex(int thisFactionIndex) 							{this->thisFactionIndex= thisFactionIndex;}
	void setFactionCount(int factionCount)									{this->factionCount= factionCount;} 
	void setTeam(int factionIndex, int team)								{this->teams[factionIndex]= team;}
	void setStartLocationIndex(int factionIndex, int startLocationIndex)	{this->startLocationIndex[factionIndex]= startLocationIndex;}

	void setDefaultUnits(bool defaultUnits) 						{this->defaultUnits= defaultUnits;}
	void setDefaultResources(bool defaultResources) 				{this->defaultResources= defaultResources;}
	void setDefaultVictoryConditions(bool defaultVictoryConditions) {this->defaultVictoryConditions= defaultVictoryConditions;}
};

}//end namespace

#endif
