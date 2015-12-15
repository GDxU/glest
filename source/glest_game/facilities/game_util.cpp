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

#include "game_util.h"

#include "util.h"
#include "lang.h"
#include "game_constants.h"
#include "config.h"



namespace Glest {

const std::string mailString= "contact_game@glest.org";
const std::string glestVersionString= "v3.2.2";

std::string getCrashDumpFileName(){
	return "glest"+glestVersionString+".dmp";
}

std::string getNetworkVersionString(){
    return glestVersionString + " - " + std::string(__DATE__) + " - " + std::string(__TIME__);
}

std::string getAboutString1(int i){
	switch(i){
	case 0: return "Glest " + glestVersionString + " (" + "Shared Library " + sharedLibVersionString + ")";
    case 1: return "Built: " + std::string(__DATE__);
	case 2: return "Copyright 2001-2009 The Glest Team";
	}
	return "";
}

std::string getAboutString2(int i){
	switch(i){
	case 0: return "Web: http://glest.org";
	case 1: return "Mail: " + mailString;
	case 2: return "Irc: irc://irc.freenode.net/glest";
	}
	return "";
}

std::string getTeammateName(int i){
	switch(i){
	case 0: return "Martiño Figueroa";
	case 1: return "Jos?Luis González";
	case 2: return "Tucho Fernández";
	case 3: return "Jos?Zanni";
	case 4: return "Félix Menéndez";
	case 5: return "Marcos Caruncho";
	case 6: return "Matthias Braun";
	}
	return "";
}

std::string getTeammateRole(int i){
	Lang &l= Lang::getInstance();

	switch(i){
	case 0: return l.get("Programming");
	case 1: return l.get("SoundAndMusic");
	case 2: return l.get("3dAnd2dArt");
	case 3: return l.get("2dArtAndWeb");
	case 4: return l.get("Animation");
	case 5: return l.get("3dArt");
	case 6: return l.get("LinuxPort");
	}
	return "";
}

std::string formatString(const std::string &str){
	std::string outStr = str;

	if(!outStr.empty()){
		outStr[0]= toupper(outStr[0]);
	}

	bool afterSeparator= false;
	for(int i= 0; i<str.size(); ++i){
		if(outStr[i]=='_'){
			outStr[i]= ' ';
		}
		else if(afterSeparator){
			outStr[i]= toupper(outStr[i]);
			afterSeparator= false;
		}
		if(outStr[i]=='\n' || outStr[i]=='(' || outStr[i]==' '){
			afterSeparator= true;
		}
	}
	return outStr;
}

}//end namespace
