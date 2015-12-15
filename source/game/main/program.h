

#ifndef _GLEST_GAME_PROGRAM_H_
#define _GLEST_GAME_PROGRAM_H_

#include "context.h"
#include "platform_util.h"
#include "window_gl.h"
#include "socket.h"
#include "window.h"



namespace Glest {

class Program;
class MainWindow;

// =====================================================
// 	class ProgramState  
//
///	Base class for all program states: 
/// Intro, MainMenu, Game, BattleEnd (State Design pattern)
// =====================================================

class ProgramState{
protected:
	Program *program;

public:
	ProgramState(Program *program)	{this->program= program;}
	virtual ~ProgramState(){};

	virtual void render()=0;
	virtual void update(){};
	virtual void updateCamera(){};
	virtual void tick(){};
	virtual void init(){};
	virtual void load(){};
	virtual void end(){};
	virtual void mouseDownLeft(int x, int y){};
	virtual void mouseUpLeft(int x, int y){};
	virtual void mouseDownRight(int x, int y){};
	virtual void mouseDoubleClickLeft(int x, int y){};
	virtual void mouseMove(int x, int y, const MouseState *mouseState){};
	virtual void keyDown(char key){};
	virtual void keyUp(char key){};
	virtual void keyPress(char c){};
};

// ===============================
// 	class Program  
// ===============================

class Program{
private:
	static const int maxTimes;

private:
    ProgramState *programState;
		    
	PerformanceTimer fpsTimer;
	PerformanceTimer updateTimer;
	PerformanceTimer updateCameraTimer;

    WindowGl *window;

public:
    Program();
    ~Program();

	void initNormal(WindowGl *window);
	void initServer(WindowGl *window);
	void initClient(WindowGl *window, const Ip &serverIp);
	
	//main
    void mouseDownLeft(int x, int y);
    void mouseUpLeft(int x, int y);
    void mouseDownRight(int x, int y);
    void mouseDoubleClickLeft(int x, int y);
    void mouseMove(int x, int y, const MouseState *mouseState);
    void keyDown(char key);
    void keyUp(char key);
    void keyPress(char c);
	void loop();
	void resize(SizeState sizeState);

	//misc
	void setState(ProgramState *programState);
	void exit();
	
private:
	void init(WindowGl *window);
	void setDisplaySettings();
	void restoreDisplaySettings();
};

} //end namespace

#endif
