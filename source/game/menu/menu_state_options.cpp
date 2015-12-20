

#include "menu_state_options.h"

#include "renderer.h"
#include "sound_renderer.h"
#include "core_data.h"
#include "config.h"
#include "menu_state_root.h"
#include "util.h"




namespace Glest {

// =====================================================
// 	class MenuStateOptions
// =====================================================

MenuStateOptions::MenuStateOptions(Program *program, MainMenu *mainMenu): 
	MenuState(program, mainMenu, "config")
{
	Lang &lang= Lang::getInstance();
	Config &config= Config::getInstance();

	//list boxes
	GraphicListBox* listBoxVolumeFx        = _ui.addListBox(350, 530, 80, 25); listBoxVolumeFx->setId(11);
	GraphicListBox* listBoxVolumeAmbient   = _ui.addListBox(350, 500, 80, 25); listBoxVolumeAmbient->setId(12);
	GraphicListBox* listBoxVolumeMusic     = _ui.addListBox(350, 470, 80, 25); listBoxVolumeMusic->setId(13);
	//GraphicListBox* listBoxMusicSelect     = _ui.addListBox(350, 440, 150, 25); listBoxMusicSelect->setId(14);
	GraphicListBox* listBoxLang            = _ui.addListBox(350, 400, 170, 25); listBoxLang->setId(15);
	GraphicListBox* listBoxFilter          = _ui.addListBox(350, 340, 170, 25); listBoxFilter->setId(16);
	GraphicListBox* listBoxShadows         = _ui.addListBox(350, 310, 170, 25); listBoxShadows->setId(17);
	GraphicListBox* listBoxTextures3D      = _ui.addListBox(350, 280, 80, 25); listBoxTextures3D->setId(18);
	GraphicListBox* listBoxLights          = _ui.addListBox(350, 250, 80, 25); listBoxLights->setId(19);

    _ui.addLabel(lang.get("FxVolume"), 200, 530);
    _ui.addLabel(lang.get("AmbientVolume"), 200, 500);
    _ui.addLabel(lang.get("MusicVolume"), 200, 470);
	_ui.addLabel(lang.get("Language"), 200, 400);
    _ui.addLabel(lang.get("Filter"), 200, 340);
	_ui.addLabel(lang.get("Shadows"), 200, 310);
	_ui.addLabel(lang.get("Textures3D"), 200, 280);
	_ui.addLabel(lang.get("MaxLights"), 200, 250);

	_ui.addButton(lang.get("Return"), 200, 150, 125, 25)->setId(1);
	_ui.addButton(lang.get("AutoConfig"), 375, 150, 125, 25)->setId(2);


	//lang
    std::vector<std::string> langResults;
	findAll("data/lang/*.lng", langResults, true);

	for (std::string& lang : langResults)
	{
		listBoxLang->pushBackItem(lang);
	}

	listBoxLang->setSelectedItem(config.getString("Lang"));
	
	//shadows
	for(int i= 0; i<Renderer::sCount; ++i){
		listBoxShadows->pushBackItem(lang.get(Renderer::shadowsToStr(static_cast<Renderer::Shadows>(i))));
	}

	std::string str= config.getString("Shadows");
	listBoxShadows->setSelectedItemIndex(clamp(Renderer::strToShadows(str), 0, Renderer::sCount-1));

	//filter
	listBoxFilter->pushBackItem("Bilinear");
	listBoxFilter->pushBackItem("Trilinear");
	listBoxFilter->setSelectedItem(config.getString("Filter"));

	//textures 3d
	listBoxTextures3D->pushBackItem(lang.get("No"));
	listBoxTextures3D->pushBackItem(lang.get("Yes"));
	listBoxTextures3D->setSelectedItemIndex(clamp(config.getInt("Textures3D"), 0, 1));

	//lights
	for(int i= 1; i<=8; ++i){
		listBoxLights->pushBackItem(intToStr(i));
	}
	listBoxLights->setSelectedItemIndex(clamp(config.getInt("MaxLights")-1, 0, 7));

	//sound
	for(int i=0; i<=100; i+=5){
		listBoxVolumeFx->pushBackItem(intToStr(i));
		listBoxVolumeAmbient->pushBackItem(intToStr(i));
		listBoxVolumeMusic->pushBackItem(intToStr(i));
	}
	listBoxVolumeFx->setSelectedItem(intToStr(config.getInt("SoundVolumeFx")/5*5));
	listBoxVolumeAmbient->setSelectedItem(intToStr(config.getInt("SoundVolumeAmbient")/5*5));
	listBoxVolumeMusic->setSelectedItem(intToStr(config.getInt("SoundVolumeMusic")/5*5));
}

void MenuStateOptions::mouseClick(int x, int y, MouseButton mouseButton){

	Config &config= Config::getInstance();
	Lang &lang= Lang::getInstance();
	CoreData &coreData= CoreData::getInstance();
	SoundRenderer &soundRenderer= SoundRenderer::getInstance();

	Widget* w = _ui.mouseClick(x, y);
	GraphicListBox* listbox = dynamic_cast<GraphicListBox*>(w);

	if (!w) return;

	switch (w->getId())
	{
	case 1:
		soundRenderer.playFx(coreData.getClickSoundA());
		mainMenu->setState(new MenuStateRoot(program, mainMenu));
		break;
	case 2:
		soundRenderer.playFx(coreData.getClickSoundA());
		Renderer::getInstance().autoConfig();
		mainMenu->setState(new MenuStateOptions(program, mainMenu));
		break;
	case 11:
		config.setString("SoundVolumeFx", listbox->getSelectedItem());
		break;
	case 12:
		config.setString("SoundVolumeAmbient", listbox->getSelectedItem());
		break;
	case 13:
		CoreData::getInstance().getMenuMusic()->setVolume(strToInt(listbox->getSelectedItem()) / 100.f);
		config.setString("SoundVolumeMusic", listbox->getSelectedItem());
		break;
	case 14:
		break;
	case 15:
		config.setString("Lang", listbox->getSelectedItem());
		lang.loadStrings(config.getString("Lang"));
		mainMenu->setState(new MenuStateOptions(program, mainMenu));
		break;
	case 16:
		config.setString("Filter", listbox->getSelectedItem());
		break;
	case 17: 
		config.setString("Shadows", Renderer::shadowsToStr(static_cast<Renderer::Shadows>(listbox->getSelectedItemIndex())));
		break;
	case 18:
		config.setInt("Textures3D", listbox->getSelectedItemIndex());
		break;
	case 19:
		config.setInt("MaxLights", listbox->getSelectedItemIndex() + 1);
		break;
	default:
		break;
	}
	saveConfig();
}

void MenuStateOptions::mouseMove(int x, int y, const MouseState *ms){
	_ui.mouseMove(x, y);
}

void MenuStateOptions::render(){
	_ui.draw();
}

void MenuStateOptions::saveConfig(){
	Config &config= Config::getInstance();

	config.save();
	Renderer::getInstance().loadConfig();
	SoundRenderer::getInstance().loadConfig();
}

}//end namespace
