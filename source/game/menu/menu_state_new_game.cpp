

#include "menu_state_new_game.h" 

#include "renderer.h"
#include "sound_renderer.h"
#include "core_data.h"
#include "config.h"
#include "menu_state_custom_game.h"
#include "menu_state_scenario.h"
#include "menu_state_root.h"
#include "metrics.h"
#include "network_manager.h"
#include "network_message.h"
#include "auto_test.h"
#include "socket.h"


namespace Glest {

// =====================================================
// 	class MenuStateNewGame
// =====================================================

MenuStateNewGame::MenuStateNewGame(Program *program, MainMenu *mainMenu): 
	MenuState(program, mainMenu, "root")
{
	Lang &lang= Lang::getInstance();

	_ui.addButton(lang.get("CustomGame"), 425, 350, 150, 25)->setId(1);
	_ui.addButton(lang.get("Scenario"), 425, 310, 150, 25)->setId(2);
	_ui.addButton(lang.get("Tutorial"), 425, 270, 150, 25)->setId(3);
	_ui.addButton(lang.get("Return"), 425, 230, 150, 25)->setId(4);

	NetworkManager::getInstance().end();
}

void MenuStateNewGame::mouseClick(int x, int y, MouseButton mouseButton){

	Widget* cmp = _ui.mouseClick(x, y);

	if (!cmp) return;

	CoreData &coreData=  CoreData::getInstance();
	SoundRenderer &soundRenderer= SoundRenderer::getInstance();

	soundRenderer.playFx(coreData.getClickSoundB());

	switch (cmp->getId())
	{
	case 1: mainMenu->setState(new MenuStateCustomGame(program, mainMenu)); break;
	case 2: mainMenu->setState(new MenuStateScenario(program, mainMenu, "scenarios")); break;
	case 3: mainMenu->setState(new MenuStateScenario(program, mainMenu, "tutorials")); break;
	case 4: mainMenu->setState(new MenuStateRoot(program, mainMenu)); break;
	}
}

void MenuStateNewGame::mouseMove(int x, int y, const MouseState *ms){
	_ui.mouseMove(x, y);
}

void MenuStateNewGame::render(){
	_ui.draw();
}

void MenuStateNewGame::update(){
	if(Config::getInstance().getBool("AutoTest")){
		AutoTest::getInstance().updateNewGame(program, mainMenu);
	}
}

}//end namespace
