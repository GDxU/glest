

#ifndef _GLEST_GAME_MAIN_H_
#define _GLEST_GAME_MAIN_H_

#include <ctime>
#include "SDL_events.h"
#include "types.h"
#include <string>
#include "BaseManager.h"



namespace Glest {

// =====================================================
// 	class MainWindow 
//
///	Main program window
// =====================================================
    class Program;
    class Timer;
    class PlatformContextGl;

    enum MouseButton{
        mbLeft,
        mbRight,
        mbCenter
    };

    // keycode constants (unfortunately designed after DirectInput and therefore not
    // very specific)
    // They also have to fit into a char. The positive numbers seem to be equal
    // to ascii, for the rest we have to find sensefull mappings from SDL (which is
    // alot more fine grained like left/right control instead of just control...)
    const char vkAdd = -1;
    const char vkSubtract = -2;
    const char vkAlt = -3;
    const char vkControl = -4;
    const char vkShift = -5;
    const char vkEscape = -6;
    const char vkUp = -7;
    const char vkLeft = -8;
    const char vkRight = -9;
    const char vkDown = -10;
    const char vkReturn = -11;
    const char vkBack = -12;

    struct MouseState{
        bool leftMouse;
        bool rightMouse;
        bool centerMouse;
    };

class Window : public base::BaseManager
{
private:
    Program* program;

public:
	Window(Program *program);
	~Window();

	void setProgram(Program *program)	{this->program= program;}

private:

    Uint32 lastMouseDown[3];
    int lastMouseX[3];
    int lastMouseY[3];

public:
    bool handleEvent();

    //object state
    void setText(std::string text);
    void setEnabled(bool enabled);
    void setVisible(bool visible);

    void showCursor(bool show);

    void destroy();
    void minimize();

    virtual void eventMouseDown(int x, int y, MouseButton mouseButton);
    virtual void eventMouseUp(int x, int y, MouseButton mouseButton);
    virtual void eventMouseMove(int x, int y, const MouseState* mouseState);
    virtual void eventMouseDoubleClick(int x, int y, MouseButton mouseButton);
    virtual void eventKeyDown(char key);
    virtual void eventKeyUp(char key);
    virtual void eventKeyPress(char c);
    virtual void eventActivate(bool activated);
    virtual void eventClose();


    /// needed to detect double clicks
    void handleMouseDown(SDL_Event event);

    static MouseButton getMouseButton(int sdlButton);
    static char getKey(SDL_Keysym keysym);
    void toggleFullscreen();
};

}//end namespace

#endif
