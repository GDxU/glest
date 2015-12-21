

#ifndef _GLEST_GAME_MAIN_H_
#define _GLEST_GAME_MAIN_H_

#include <ctime>

#include "program.h"
#include "window.h"




namespace Glest {

// =====================================================
// 	class MainWindow 
//
///	Main program window
// =====================================================

class MainWindow: public Window
{
private:
    Program* program;

public:
	MainWindow(Program *program);
	~MainWindow();

	void setProgram(Program *program)	{this->program= program;}

	virtual void eventMouseDown(int x, int y, MouseButton mouseButton);
	virtual void eventMouseUp(int x, int y, MouseButton mouseButton);
	virtual void eventMouseDoubleClick(int x, int y, MouseButton mouseButton);
	virtual void eventMouseMove(int x, int y, const MouseState *mouseState);
	virtual void eventKeyDown(char key);
	virtual void eventKeyUp(char key);
	virtual void eventKeyPress(char c);
	virtual void eventActivate(bool active);
	virtual void eventResize(SizeState sizeState);
	virtual void eventClose();
};

}//end namespace

#endif
