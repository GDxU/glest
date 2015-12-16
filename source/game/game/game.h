

#ifndef _GLEST_GAME_GAME_H_
#define _GLEST_GAME_GAME_H_

#include <vector>

#include "gui.h"
#include "game_camera.h"
#include "world.h"
#include "ai_interface.h"
#include "program.h"
#include "chat_manager.h"
#include "script_manager.h"
#include "game_settings.h"




namespace Glest {

class GraphicMessageBox;

// =====================================================
// 	class Game
//
//	Main game class
// =====================================================

class Game: public ProgramState{
public:
	enum Speed{
		sFast,
		sNormal,
		sSlow
	};

private:
	typedef std::vector<Ai*> Ais;
	typedef std::vector<AiInterface*> AiInterfaces;

private:
	//main data
	World world;
    AiInterfaces aiInterfaces;
    Gui gui;
    GameCamera gameCamera;
    Commander commander;
    Console console;
	ChatManager chatManager;
	ScriptManager scriptManager;

	//misc
	Checksum checksum;
    std::string loadingText;
    int mouse2d;
    int mouseX, mouseY; //coords win32Api
	int updateFps, lastUpdateFps;
	int renderFps, lastRenderFps;
	bool paused;
	bool gameOver;
	bool renderNetworkStatus;
	Speed speed;
	GraphicMessageBox mainMessageBox;

	//misc ptr
	ParticleSystem *weatherParticleSystem;
	GameSettings gameSettings;

public:
    Game(Program *program, const GameSettings *gameSettings);
    ~Game();

    //get
	GameSettings *getGameSettings()			{return &gameSettings;}
	
	const GameCamera *getGameCamera() const	{return &gameCamera;}
	GameCamera *getGameCamera()				{return &gameCamera;}
	const Commander *getCommander() const	{return &commander;}
	Gui *getGui()							{return &gui;}
	const Gui *getGui() const				{return &gui;}
	Commander *getCommander()				{return &commander;}
	Console *getConsole()					{return &console;}
	ScriptManager *getScriptManager()		{return &scriptManager;}
	World *getWorld()						{return &world;}
	const World *getWorld() const			{return &world;}

    //init
    virtual void load();
    virtual void init();
    virtual void update(float);
	virtual void updateCamera();
	virtual void render();
	virtual void tick();

    //event managing
    virtual void keyDown(char key);
    virtual void keyUp(char key);
    virtual void keyPress(char c);
    virtual void mouseDownLeft(int x, int y);
    virtual void mouseDownRight(int x, int y);
    virtual void mouseUpLeft(int x, int y);
    virtual void mouseDoubleClickLeft(int x, int y);
    virtual void mouseMove(int x, int y, const MouseState *mouseState);

	void quitGame();
private:
	//render
    void render3d();
    void render2d();

	//misc
	void checkWinner();
	void checkWinnerStandard();
	void checkWinnerScripted();
	bool hasBuilding(const Faction *faction);
	void incSpeed();
	void decSpeed();
	int getUpdateLoops();
	void showLoseMessageBox();
	void showWinMessageBox();
	void showMessageBox(const std::string &text, const std::string &header, bool toggle);
};

}//end namespace

#endif
