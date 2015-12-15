

#ifndef _GLEST_GAME_MENUSTATEOPTIONS_H_
#define _GLEST_GAME_MENUSTATEOPTIONS_H_

#include "main_menu.h"

namespace Glest {

// ===============================
// 	class MenuStateOptions  
// ===============================

class MenuStateOptions: public MenuState{
private:
	GraphicButton buttonReturn;	
	GraphicButton buttonAutoConfig;	
	
	GraphicLabel labelLang;
	GraphicLabel labelShadows;
	GraphicLabel labelFilter;
	GraphicLabel labelTextures3D;
	GraphicLabel labelLights;
	GraphicLabel labelVolumeFx;
	GraphicLabel labelVolumeAmbient;
	GraphicLabel labelVolumeMusic;
	GraphicListBox listBoxLang;
	GraphicListBox listBoxShadows;
	GraphicListBox listBoxFilter;
	GraphicListBox listBoxTextures3D;
	GraphicListBox listBoxLights;
	GraphicListBox listBoxVolumeFx;
	GraphicListBox listBoxVolumeAmbient;
	GraphicListBox listBoxVolumeMusic;
	GraphicListBox listBoxMusicSelect;

public:
	MenuStateOptions(Program *program, MainMenu *mainMenu);

	void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();

private:
	void saveConfig();
};

}//end namespace

#endif
