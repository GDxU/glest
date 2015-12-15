

#ifndef _GLEST_GAME_MENUSTATEGRAPHICINFO_H_
#define _GLEST_GAME_MENUSTATEGRAPHICINFO_H_

#include "main_menu.h"

namespace Glest {

// ===============================
// 	class MenuStateGraphicInfo  
// ===============================

class MenuStateGraphicInfo: public MenuState{
private:
	GraphicButton buttonReturn;
	GraphicLabel labelInfo;
	GraphicLabel labelMoreInfo;

	std::string glInfo;
	std::string glMoreInfo;
public:
	MenuStateGraphicInfo(Program *program, MainMenu *mainMenu);

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();
};

}//end namespace

#endif
