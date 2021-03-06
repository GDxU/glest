

#ifndef _GLEST_GAME_MENUSTATEJOINGAME_H_
#define _GLEST_GAME_MENUSTATEJOINGAME_H_

#include "properties.h"
#include "main_menu.h"



namespace Glest {

class NetworkMessageIntro;

// ===============================
// 	class MenuStateJoinGame  
// ===============================

class MenuStateJoinGame: public MenuState{
private:
	static const int newServerIndex;
	static const std::string serverFileName;

private:
	GraphicButton buttonReturn;
	GraphicButton buttonConnect;
	GraphicLabel labelServer;
	GraphicLabel labelServerType;
	GraphicLabel labelServerIp;
	GraphicLabel labelStatus;
	GraphicLabel labelInfo;
	GraphicListBox listBoxServerType;
	GraphicListBox listBoxServers;

	bool connected;
	int playerIndex;
	Properties servers;

public:
	MenuStateJoinGame(Program *program, MainMenu *mainMenu, bool connect= false, Ip serverIp= Ip());

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();
	void update();
	void keyDown(char key);
	void keyPress(char c);

private:
	void connectToServer();
};
}//end namespace

#endif
