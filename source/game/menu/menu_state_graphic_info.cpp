

#include "menu_state_graphic_info.h"

#include "renderer.h"
#include "sound_renderer.h"
#include "core_data.h"
#include "menu_state_options.h"


namespace Glest {

// =====================================================
// 	class MenuStateGraphicInfo
// =====================================================

MenuStateGraphicInfo::MenuStateGraphicInfo(Program *program, MainMenu *mainMenu): 
	MenuState(program, mainMenu, "info")
{
	buttonReturn.init(387, 100, 125, 25);
	labelInfo.init(100, 700);
	labelMoreInfo.init(100, 500);
	labelMoreInfo.setFont(CoreData::getInstance().getMenuFontSmall());

	Renderer &renderer= Renderer::getInstance();
	glInfo= renderer.getGlInfo();
	glMoreInfo= renderer.getGlMoreInfo();
}

void MenuStateGraphicInfo::mouseClick(int x, int y, MouseButton mouseButton){
	CoreData &coreData= CoreData::getInstance();
	SoundRenderer &soundRenderer= SoundRenderer::getInstance();

	if(buttonReturn.mouseClick(x,y)){
		soundRenderer.playFx(coreData.getClickSoundA());
		mainMenu->setState(new MenuStateOptions(program, mainMenu));
    }     
}

void MenuStateGraphicInfo::mouseMove(int x, int y, const MouseState *ms){
	buttonReturn.mouseMove(x, y);
}

void MenuStateGraphicInfo::render(){
	
	Renderer &renderer= Renderer::getInstance();
	Lang &lang= Lang::getInstance();
	
	buttonReturn.setText(lang.get("Return"));
	labelInfo.setText(glInfo);
	labelMoreInfo.setText(glMoreInfo);

	renderer.renderButton(&buttonReturn);
	renderer.renderLabel(&labelInfo);
	renderer.renderLabel(&labelMoreInfo);
}

}//end namespace
