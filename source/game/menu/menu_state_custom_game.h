

#ifndef _GLEST_GAME_MENUSTATECUSTOMGAME_H_
#define _GLEST_GAME_MENUSTATECUSTOMGAME_H_

#include "main_menu.h"

namespace Glest {

// ===============================
// 	class MenuStateCustomGame  
// ===============================

class MenuStateCustomGame: public MenuState{
private:
	GraphicButton buttonReturn;
	GraphicButton buttonPlayNow;
	GraphicLabel labelControl;
	GraphicLabel labelFaction;
	GraphicLabel labelTeam;
	GraphicLabel labelMap;
	GraphicLabel labelTechTree;
	GraphicLabel labelTileset;
	GraphicLabel labelMapInfo;
	GraphicListBox listBoxMap;
	GraphicListBox listBoxTechTree;
	GraphicListBox listBoxTileset;
    std::vector<std::string> mapFiles;
    std::vector<std::string> techTreeFiles;
    std::vector<std::string> tilesetFiles;
    std::vector<std::string> factionFiles;
	GraphicLabel labelPlayers[GameConstants::maxPlayers];
	GraphicListBox listBoxControls[GameConstants::maxPlayers];
	GraphicListBox listBoxFactions[GameConstants::maxPlayers];
	GraphicListBox listBoxTeams[GameConstants::maxPlayers];
	GraphicLabel labelNetStatus[GameConstants::maxPlayers];
	MapInfo mapInfo;

public:
	MenuStateCustomGame(Program *program, MainMenu *mainMenu, bool openNetworkSlots= false);

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();
	void update();

private:
    void loadGameSettings(GameSettings *gameSettings);
	void loadMapInfo(std::string file, MapInfo *mapInfo);
	void reloadFactions();
	void updateControlers();
	void closeUnusedSlots();
	void updateNetworkSlots();
};

}//end namespace

#endif
