

#ifndef _GLEST_GAME_MENUSTATESCENARIO_H_
#define _GLEST_GAME_MENUSTATESCENARIO_H_

#include "main_menu.h"

namespace Glest {

// ===============================
// 	class MenuStateScenario
// ===============================

class MenuStateScenario: public MenuState{
private:
    enum Difficulty{
        dVeryEasy,
        dEasy,
        dMedium,
        dHard,
        dVeryHard,
        dInsane
    };

	GraphicButton buttonReturn;
	GraphicButton buttonPlayNow;

	GraphicLabel labelInfo;
	GraphicLabel labelScenario;
	GraphicListBox listBoxScenario;
    
    std::vector<std::string> scenarioFiles;

    ScenarioInfo scenarioInfo;
	std::string dir;

public:
	MenuStateScenario(Program *program, MainMenu *mainMenu, const std::string &dir);

    void mouseClick(int x, int y, MouseButton mouseButton);
	void mouseMove(int x, int y, const MouseState *mouseState);
	void render();
	void update();

	void launchGame();
	void setScenario(int i);
	int getScenarioCount() const	{ return listBoxScenario.getItemCount(); }
	
private:
    void loadScenarioInfo(std::string file, ScenarioInfo *scenarioInfo);
    void loadGameSettings(const ScenarioInfo *scenarioInfo, GameSettings *gameSettings);
	Difficulty computeDifficulty(const ScenarioInfo *scenarioInfo);
    ControlType strToControllerType(const std::string &str);

};


}//end namespace

#endif
