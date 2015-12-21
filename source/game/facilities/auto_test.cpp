

#include "auto_test.h"

#include "program.h"
#include "main_menu.h"
#include "menu_state_new_game.h"
#include "menu_state_scenario.h"
#include "game.h"


namespace Glest {

// =====================================================
//	class AutoTest
// =====================================================

const time_t AutoTest::invalidTime = -1;
const time_t AutoTest::gameTime = 60*20;

// ===================== PUBLIC ======================== 

AutoTest::AutoTest(){
	gameStartTime = invalidTime;
	random.init();
}

AutoTest & AutoTest::getInstance(){
	static AutoTest autoTest;
	return autoTest;
}

void AutoTest::updateIntro(Program *program){
	program->setState(new MainMenu(program));
}

void AutoTest::updateRoot(Program *program, MainMenu *mainMenu){
	mainMenu->setState(new MenuStateNewGame(program, mainMenu));
}

void AutoTest::updateNewGame(Program *program, MainMenu *mainMenu){
	mainMenu->setState(new MenuStateScenario(program, mainMenu, "scenarios"));
}

void AutoTest::updateScenario(MenuStateScenario *menuStateScenario){
	gameStartTime = invalidTime;

	int scenarioIndex = random.randRange(0, menuStateScenario->getScenarioCount()-1);
	menuStateScenario->setScenario(scenarioIndex);

	menuStateScenario->launchGame();
}

void AutoTest::updateGame(Game *game){
	
	// record start time
	if(gameStartTime==invalidTime)
	{
		gameStartTime = time(NULL);
	}

	// quit if we've espend enough time in the game
	if(time(NULL)-gameStartTime>gameTime){
		game->quitGame();
	}
}

void AutoTest::updateBattleEnd(Program *program){
	program->setState(new MainMenu(program));
}

}//end namespace
