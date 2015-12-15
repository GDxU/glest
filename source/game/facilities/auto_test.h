

#ifndef _SHARED_UTIL_AUTO_TEST_H_
#define _SHARED_UTIL_AUTO_TEST_H_

#include <ctime>

#include "random.h"



namespace Glest {

class Program;
class MainMenu;
class MenuStateScenario;
class Game;

// =====================================================
//	class AutoTest  
//
/// Interface to write log files
// =====================================================

class AutoTest{
private:
	int gameStartTime;
	Random random;

private:
	static const time_t invalidTime;
	static const time_t gameTime;

public:
	static AutoTest & getInstance();
	AutoTest();

	void updateIntro(Program *program);
	void updateRoot(Program *program, MainMenu *mainMenu);
	void updateNewGame(Program *program, MainMenu *mainMenu);
	void updateScenario(MenuStateScenario *menuStateScenario);
	void updateGame(Game *game);
	void updateBattleEnd(Program *program);
};

}//end namespace

#endif
