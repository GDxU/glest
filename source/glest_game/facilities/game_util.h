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

#ifndef _GLEST_GAME_GAMEUTIL_H_
#define _GLEST_GAME_GAMEUTIL_H_

#include <string>
#include <vector>

#include "util.h"





namespace Glest {

extern const std::string mailString;
extern const std::string glestVersionString;
extern const std::string networkVersionString;

std::string getCrashDumpFileName();
std::string getNetworkVersionString();
std::string getAboutString1(int i);
std::string getAboutString2(int i);
std::string getTeammateName(int i);
std::string getTeammateRole(int i);

std::string formatString(const std::string &str);

}//end namespace

#endif
