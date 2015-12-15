// ==============================================================
//	This file is part of Glest (www.glest.org)
//
//	Copyright (C) 2001-2008 Marti�o Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#ifndef _GLEST_GAME_CHATMANAGER_H_
#define _GLEST_GAME_CHATMANAGER_H_

#include <string>




namespace Glest {

class Console;

// =====================================================
//	class ChatManager
// =====================================================

class ChatManager{
private:
	static const int maxTextLenght;

private:
	bool editEnabled;
	bool teamMode;
	Console* console;
	std::string text;
	int thisTeamIndex;

public:
	ChatManager();
	void init(Console* console, int thisTeamIndex);

	void keyDown(char key);
	void keyPress(char c);
	void updateNetwork();

	bool getEditEnabled() const	{return editEnabled;}
	bool getTeamMode() const	{return teamMode;}
	std::string getText() const		{return text;}
};

}//end namespace

#endif
