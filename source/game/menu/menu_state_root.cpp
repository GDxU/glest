

#include "menu_state_root.h"

#include "renderer.h"
#include "sound_renderer.h"
#include "core_data.h"
#include "config.h"
#include "menu_state_new_game.h"
#include "menu_state_join_game.h"
#include "menu_state_options.h"
#include "menu_state_about.h"
#include "metrics.h"
#include "network_manager.h"
#include "network_message.h"
#include "socket.h"
#include "auto_test.h"


namespace Glest {

// =====================================================
// 	class MenuStateRoot
// =====================================================

MenuStateRoot::MenuStateRoot(Program *program, MainMenu *mainMenu): 
	MenuState(program, mainMenu, "root")
{
	Lang &lang = Lang::getInstance();

	_ui.addButton(lang.get("NewGame"), 425, 350, 150, 25)->setId(1);
	_ui.addButton(lang.get("JoinGame"), 425, 310, 150, 25)->setId(2);
	_ui.addButton(lang.get("Options"), 425, 270, 150, 25)->setId(3);
	_ui.addButton(lang.get("About"), 425, 230, 150, 25)->setId(4);
	_ui.addButton(lang.get("Exit"), 425, 190, 150, 25)->setId(5);

	const Metrics &metrics = Metrics::getInstance();
	Texture2D* tex = CoreData::getInstance().getLogoTexture();

	float w = (float)tex->getPixmap()->getW();
	float h = (float)tex->getPixmap()->getH();

	int displayW = w * 0.6f;
	int displayH = h * 0.6f;

	_ui.addImage(tex, metrics.getVirtualW() / 2 - displayW / 2, metrics.getVirtualH() / 2 + displayH / 4, displayW, displayH);

	_ui.addLabel(glestVersionString, 520, 440);
}

void MenuStateRoot::mouseClick(int x, int y, MouseButton mouseButton){
	Widget* btn = _ui.mouseMove(x, y);

	if (!btn)
		return;

	CoreData &coreData=  CoreData::getInstance();
	SoundRenderer &soundRenderer= SoundRenderer::getInstance();
	soundRenderer.playFx(coreData.getClickSoundB());

	switch (btn->getId())
	{
	case 1: mainMenu->setState<MenuStateNewGame>(); break;
	case 2: mainMenu->setState<MenuStateJoinGame>(); break;
	case 3: mainMenu->setState<MenuStateOptions>(); break;
	case 4: mainMenu->setState<MenuStateAbout>(); break;
	case 5: program->exit(); break;
	}
}

void MenuStateRoot::mouseMove(int x, int y, const MouseState *ms){
	_ui.mouseMove(x, y);
}

void MenuStateRoot::render(){
	_ui.draw();
}

void MenuStateRoot::update(){
	if(Config::getInstance().getBool("AutoTest")){
		AutoTest::getInstance().updateRoot(program, mainMenu);
	}
}

}//end namespace
