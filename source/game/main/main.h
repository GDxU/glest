

#ifndef _GLEST_GAME_MAIN_H_
#define _GLEST_GAME_MAIN_H_

#include <ctime>
#include "SDL_events.h"
#include "types.h"
#include <string>



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

class Window
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

protected:
    int w, h;
    bool _fullscreen;

public:
    static bool handleEvent();

    WindowHandle getHandle()	{ return 0; }
    std::string getText();
    int getX()					{ return 0; }
    int getY()					{ return 0; }
    int getW()					{ return w; }
    int getH()					{ return h; }

    //component state
    int getClientW()			{ return getW(); }
    int getClientH()			{ return getH(); }
    float getAspect();

    //object state
    void setText(std::string text);
    void setSize(int w, int h);
    void setPos(int x, int y);
    void setEnabled(bool enabled);
    void setVisible(bool visible);

    //misc
    void create(int w, int h, bool fullscreen);
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
    static void toggleFullscreen();

    static void swapBuffersGl();

protected:
    void initGl();
};

}//end namespace

#endif
