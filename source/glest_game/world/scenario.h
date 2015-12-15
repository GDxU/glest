// ==============================================================
//	This file is part of Glest (www.glest.org)
//
//	Copyright (C) 2001-2005 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#ifndef _GLEST_GAME_SCENARIO_H_
#define _GLEST_GAME_SCENARIO_H_

#include <string>
#include <vector>

#include "xml_parser.h"










namespace Glest {

// =====================================================
//	class Script
// =====================================================

class Script{
private:
	std::string name;
	std::string code;

public:
	Script(const std::string &name, const std::string &code)	{this->name= name; this->code= code;}

	const std::string &getName() const	{return name;}
	const std::string &getCode() const	{return code;}
};

// =====================================================
//	class Scenario
// =====================================================

class Scenario{
private:
    typedef std::pair<std::string, std::string> NameScriptPair;
	typedef std::vector<Script> Scripts;

	Scripts scripts;

public:
    ~Scenario();
	void load(const std::string &path);

	int getScriptCount() const				{return scripts.size();}
	const Script* getScript(int i) const	{return &scripts[i];}

	static std::string getScenarioPath(const std::string &dir, const std::string &scenarioName);

private:
	std::string getFunctionName(const XmlNode *scriptNode);
};

}//end namespace

#endif
