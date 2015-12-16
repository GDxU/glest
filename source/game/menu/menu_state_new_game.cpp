

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

	buttonCustomGame.init(425, 350, 150);
    buttonScenario.init(425, 310, 150);
    buttonTutorial.init(425, 270, 150);
    buttonReturn.init(425, 230, 150);

	buttonCustomGame.setText(lang.get("CustomGame"));
	buttonScenario.setText(lang.get("Scenario"));
	buttonTutorial.setText(lang.get("Tutorial"));
	buttonReturn.setText(lang.get("Return"));

	NetworkManager::getInstance().end();
}

void MenuStateNewGame::mouseClick(int x, int y, MouseButton mouseButton){

	CoreData &coreData=  CoreData::getInstance();
	SoundRenderer &soundRenderer= SoundRenderer::getInstance();

	if(buttonCustomGame.mouseClick(x, y)){
		soundRenderer.playFx(coreData.getClickSoundB());
		mainMenu->setState(new MenuStateCustomGame(program, mainMenu));
    }  
	else if(buttonScenario.mouseClick(x, y)){
		soundRenderer.playFx(coreData.getClickSoundB());
		mainMenu->setState(new MenuStateScenario(program, mainMenu, "scenarios"));
    }  
	else if(buttonTutorial.mouseClick(x, y)){
		soundRenderer.playFx(coreData.getClickSoundB());
		mainMenu->setState(new MenuStateScenario(program, mainMenu, "tutorials"));
    }     
    else if(buttonReturn.mouseClick(x, y)){ 
		soundRenderer.playFx(coreData.getClickSoundB());
		mainMenu->setState(new MenuStateRoot(program, mainMenu));
    }
}

void MenuStateNewGame::mouseMove(int x, int y, const MouseState *ms){
	buttonCustomGame.mouseMove(x, y);
    buttonScenario.mouseMove(x, y);
    buttonTutorial.mouseMove(x, y);
    buttonReturn.mouseMove(x, y);
}

void MenuStateNewGame::render(){
	Renderer &renderer= Renderer::getInstance();

	renderer.renderButton(&buttonCustomGame);
	renderer.renderButton(&buttonScenario);
	renderer.renderButton(&buttonTutorial);
	renderer.renderButton(&buttonReturn);
}

void MenuStateNewGame::update(){
	if(Config::getInstance().getBool("AutoTest")){
		AutoTest::getInstance().updateNewGame(program, mainMenu);
	}
}

}//end namespace