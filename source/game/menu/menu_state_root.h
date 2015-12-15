

#ifndef _GLEST_GAME_MENUSTATEROOT_H_
#define _GLEST_GAME_MENUSTATEROOT_H_

#include "main_menu.h"

namespace Glest {

// ===============================
// 	class MenuStateRoot  
// ===============================

class MenuStateRoot: public MenuState{
private:
	GraphicButton buttonNewGame;
	GraphicButton buttonJoinGame;
	GraphicButton buttonOptions;
	GraphicButton buttonAbout;
	GraphicButton buttonExit;
	GraphicLabel labelVersion;

public:
	MenuStateRoot(Program *program, MainMenu *mainMenu);

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();
	void update();
};


}//end namespace

#endif
