

#include "menu_state_scenario.h"

#include "renderer.h"
#include "menu_state_new_game.h"
#include "sound_renderer.h"
#include "core_data.h"
#include "menu_state_options.h"
#include "network_manager.h"
#include "config.h"
#include "auto_test.h"
#include "game.h"


namespace Glest {



// =====================================================
// 	class MenuStateScenario
// =====================================================

MenuStateScenario::MenuStateScenario(Program *program, MainMenu *mainMenu, const std::string &dir):
    MenuState(program, mainMenu, "scenario")
{
	Lang &lang= Lang::getInstance();
	NetworkManager &networkManager= NetworkManager::getInstance();
    std::vector<std::string> results;

	this->dir = dir;

    labelInfo.init(350, 350);
	labelInfo.setFont(CoreData::getInstance().getMenuFontNormal());

	buttonReturn.init(350, 200, 125, 25);
	buttonPlayNow.init(525, 200, 125, 25);

    listBoxScenario.init(350, 400, 190);
	labelScenario.init(350, 430);

	buttonReturn.setText(lang.get("Return"));
	buttonPlayNow.setText(lang.get("PlayNow"));

    labelScenario.setText(lang.get("Scenario"));

    //scenario listbox
	findAll(dir+"/*.", results);
    scenarioFiles= results;
	if(results.size()==0){
        throw std::runtime_error("There are no scenarios");
	}
	for(int i= 0; i<results.size(); ++i){
		results[i]= formatString(results[i]);
	}
    listBoxScenario.setItems(results);

    loadScenarioInfo(Scenario::getScenarioPath(dir, scenarioFiles[listBoxScenario.getSelectedItemIndex()]), &scenarioInfo );
    labelInfo.setText(scenarioInfo.desc);

	networkManager.init(nrServer);
}

void MenuStateScenario::mouseClick(int x, int y, MouseButton mouseButton){

	CoreData &coreData= CoreData::getInstance();
	SoundRenderer &soundRenderer= SoundRenderer::getInstance();

	if(buttonReturn.mouseClick(x,y)){
		soundRenderer.playFx(coreData.getClickSoundA());
		mainMenu->setState(new MenuStateNewGame(program, mainMenu));
    } 
	else if(buttonPlayNow.mouseClick(x,y)){
		soundRenderer.playFx(coreData.getClickSoundC());
		launchGame();
	}
    else if(listBoxScenario.mouseClick(x, y)){
		loadScenarioInfo(Scenario::getScenarioPath(dir, scenarioFiles[listBoxScenario.getSelectedItemIndex()]), &scenarioInfo);
        labelInfo.setText(scenarioInfo.desc);
	}
}

void MenuStateScenario::mouseMove(int x, int y, const MouseState *ms){
	
	listBoxScenario.mouseMove(x, y);

	buttonReturn.mouseMove(x, y);
	buttonPlayNow.mouseMove(x, y);
}

void MenuStateScenario::render(){

	Renderer &renderer= Renderer::getInstance();

	renderer.renderLabel(&labelInfo);
	renderer.renderLabel(&labelScenario);
	renderer.renderListBox(&listBoxScenario);

	renderer.renderButton(&buttonReturn);
	renderer.renderButton(&buttonPlayNow);
}

void MenuStateScenario::update(){
	if(Config::getInstance().getBool("AutoTest")){
		AutoTest::getInstance().updateScenario(this);
	}
}

void MenuStateScenario::launchGame(){
	GameSettings gameSettings;
    loadGameSettings(&scenarioInfo, &gameSettings);
	program->setState(new Game(program, &gameSettings));
}

void MenuStateScenario::setScenario(int i){
	listBoxScenario.setSelectedItemIndex(i);
	loadScenarioInfo(Scenario::getScenarioPath(dir, scenarioFiles[listBoxScenario.getSelectedItemIndex()]), &scenarioInfo);
}

void MenuStateScenario::loadScenarioInfo(std::string file, ScenarioInfo *scenarioInfo){
	
    Lang &lang= Lang::getInstance();
    
    XmlTree xmlTree;
	xmlTree.load(file);

    const XmlNode *scenarioNode= xmlTree.getRootNode();
	const XmlNode *difficultyNode= scenarioNode->getChild("difficulty");
	scenarioInfo->difficulty = difficultyNode->getAttribute("value")->getIntValue();
	if( scenarioInfo->difficulty < dVeryEasy || scenarioInfo->difficulty > dInsane )
	{
		throw std::runtime_error("Invalid difficulty");
	}

	const XmlNode *playersNode= scenarioNode->getChild("players");
    for(int i= 0; i<GameConstants::maxPlayers; ++i){
        const XmlNode* playerNode = playersNode->getChild("player", i);
        ControlType factionControl = strToControllerType( playerNode->getAttribute("control")->getValue() );
        std::string factionTypeName;

        scenarioInfo->factionControls[i] = factionControl;

        if(factionControl != ctClosed){
            int teamIndex = playerNode->getAttribute("team")->getIntValue();

            if( teamIndex < 1 || teamIndex > GameConstants::maxPlayers )
            {
                throw std::runtime_error("Team out of range: " + intToStr(teamIndex));
            }

            scenarioInfo->teams[i]= playerNode->getAttribute("team")->getIntValue();
            scenarioInfo->factionTypeNames[i]= playerNode->getAttribute("faction")->getValue();
        }

        scenarioInfo->mapName = scenarioNode->getChild("map")->getAttribute("value")->getValue();
        scenarioInfo->tilesetName = scenarioNode->getChild("tileset")->getAttribute("value")->getValue();
        scenarioInfo->techTreeName = scenarioNode->getChild("tech-tree")->getAttribute("value")->getValue();
        scenarioInfo->defaultUnits = scenarioNode->getChild("default-units")->getAttribute("value")->getBoolValue();
        scenarioInfo->defaultResources = scenarioNode->getChild("default-resources")->getAttribute("value")->getBoolValue();
        scenarioInfo->defaultVictoryConditions = scenarioNode->getChild("default-victory-conditions")->getAttribute("value")->getBoolValue();
    }

	//add player info
    scenarioInfo->desc= lang.get("Player") + ": ";
	for(int i=0; i<GameConstants::maxPlayers; ++i )
	{
		if(scenarioInfo->factionControls[i] == ctHuman )
		{
			scenarioInfo->desc+= formatString(scenarioInfo->factionTypeNames[i]);
			break;
		}
	}
	
	//add misc info
	std::string difficultyString = "Difficulty" + intToStr(scenarioInfo->difficulty);

	scenarioInfo->desc+= "\n";
    scenarioInfo->desc+= lang.get("Difficulty") + ": " + lang.get(difficultyString) +"\n";
    scenarioInfo->desc+= lang.get("Map") + ": " + formatString(scenarioInfo->mapName) + "\n";
    scenarioInfo->desc+= lang.get("Tileset") + ": " + formatString(scenarioInfo->tilesetName) + "\n";
	scenarioInfo->desc+= lang.get("TechTree") + ": " + formatString(scenarioInfo->techTreeName) + "\n";
}

void MenuStateScenario::loadGameSettings(const ScenarioInfo *scenarioInfo, GameSettings *gameSettings){

	int factionCount= 0;

	gameSettings->setDescription(formatString(scenarioFiles[listBoxScenario.getSelectedItemIndex()]));
	gameSettings->setMap(scenarioInfo->mapName);
    gameSettings->setTileset(scenarioInfo->tilesetName);
    gameSettings->setTech(scenarioInfo->techTreeName);
	gameSettings->setScenario(scenarioFiles[listBoxScenario.getSelectedItemIndex()]);
	gameSettings->setScenarioDir(dir);
	gameSettings->setDefaultUnits(scenarioInfo->defaultUnits);
	gameSettings->setDefaultResources(scenarioInfo->defaultResources);
	gameSettings->setDefaultVictoryConditions(scenarioInfo->defaultVictoryConditions);

    for(int i=0; i<GameConstants::maxPlayers; ++i){
        ControlType ct= static_cast<ControlType>(scenarioInfo->factionControls[i]);
		if(ct!=ctClosed){
			if(ct==ctHuman){
				gameSettings->setThisFactionIndex(factionCount);
			}
			gameSettings->setFactionControl(factionCount, ct);
            gameSettings->setTeam(factionCount, scenarioInfo->teams[i]-1);
			gameSettings->setStartLocationIndex(factionCount, i);
            gameSettings->setFactionTypeName(factionCount, scenarioInfo->factionTypeNames[i]);
			factionCount++;
		}
    }

	gameSettings->setFactionCount(factionCount);
}

ControlType MenuStateScenario::strToControllerType(const std::string &str){
    if(str=="closed"){
        return ctClosed;
    }
    else if(str=="cpu"){
	    return ctCpu;
    }
    else if(str=="cpu-ultra"){ 
        return ctCpuUltra;
    }
    else if(str=="human"){
	    return ctHuman;
    }

    throw std::runtime_error("Unknown controller type: " + str);
}

}//end namespace
