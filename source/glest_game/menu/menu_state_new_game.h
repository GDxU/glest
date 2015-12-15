

#ifndef _GLEST_GAME_MENUSTATENEWGAME_H_
#define _GLEST_GAME_MENUSTATENEWGAME_H_

#include "main_menu.h"

namespace Glest {

// ===============================
// 	class MenuStateNewGame  
// ===============================

class MenuStateNewGame: public MenuState{
private:
	GraphicButton buttonCustomGame;
	GraphicButton buttonScenario;
	GraphicButton buttonTutorial;
	GraphicButton buttonReturn;

public:
	MenuStateNewGame(Program *program, MainMenu *mainMenu);

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void update();
	void render();
};


}//end namespace

#endif
