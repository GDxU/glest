

#ifndef _GLEST_GAME_MENUSTATEABOUT_H_
#define _GLEST_GAME_MENUSTATEABOUT_H_

#include "main_menu.h"

namespace Glest {

// ===============================
// 	class MenuStateAbout  
// ===============================

class MenuStateAbout: public MenuState{
public:
	static const int aboutStringCount1= 3;
	static const int aboutStringCount2= 3;
	static const int teammateCount= 7;

private:
	GraphicButton buttonReturn;
	GraphicLabel labelAbout1[aboutStringCount1];
	GraphicLabel labelAbout2[aboutStringCount2];
	GraphicLabel labelTeammateName[teammateCount];
	GraphicLabel labelTeammateRole[teammateCount];

public:
	MenuStateAbout(Program *program, MainMenu *mainMenu);

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();
};

}//end namespace

#endif