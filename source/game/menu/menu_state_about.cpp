

#include "menu_state_about.h"

#include "renderer.h"
#include "menu_state_root.h"
#include "sound_renderer.h"
#include "core_data.h"
#include "menu_state_options.h"


namespace Glest {

// =====================================================
// 	class MenuStateAbout
// =====================================================

MenuStateAbout::MenuStateAbout(Program *program, MainMenu *mainMenu):
	MenuState(program, mainMenu, "about")
{
	Lang &lang= Lang::getInstance();
	
	_ui.addButton(lang.get("Return"), 460, 100, 125, 25);
	
	_ui.addLabel("Glest " + glestVersionString + " (" + "Shared Library " + sharedLibVersionString + ")", 100, 650 - 0 * 20);
	_ui.addLabel("Built: " + std::string(__DATE__), 100, 650 - 1 * 20);
	_ui.addLabel("Copyright 2001-2009 The Glest Team", 100, 650 - 2 * 20);

	_ui.addLabel("Web: http://glest.org", 460, 650 - 0 * 20);
	_ui.addLabel("Mail: " + mailString, 460, 650 - 1 * 20);
	_ui.addLabel("Irc: irc://irc.freenode.net/glest", 460, 650 - 2 * 20);

	for (int i = 0; i < 7; ++i){
		_ui.addLabel(getTeammateName(i), 100 + i * 180, 500);
		_ui.addLabel(getTeammateRole(i), 100 + i * 180, 520);
	}
}

void MenuStateAbout::mouseClick(int x, int y, MouseButton mouseButton){

	Widget* w = _ui.mouseClick(x, y);
	
	if (!w) return;

	CoreData &coreData=  CoreData::getInstance();
	SoundRenderer &soundRenderer= SoundRenderer::getInstance();
	soundRenderer.playFx(coreData.getClickSoundA());

	mainMenu->setState(new MenuStateRoot(program, mainMenu));
}

void MenuStateAbout::mouseMove(int x, int y, const MouseState *ms){
	_ui.mouseMove(x, y);
}

void MenuStateAbout::render(){
	_ui.draw();
}

}//end namespace
