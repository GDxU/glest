

#ifndef _GLEST_GAME_MENUSTATEABOUT_H_
#define _GLEST_GAME_MENUSTATEABOUT_H_

#include "main_menu.h"

namespace Glest {

// ===============================
// 	class MenuStateAbout  
// ===============================

class MenuStateAbout: public MenuState{
public:
	UI _ui;

	MenuStateAbout(Program *program, MainMenu *mainMenu);

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();
};

}//end namespace

#endif
