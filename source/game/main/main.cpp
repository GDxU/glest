

#include "main.h"

#include <string>
#include <cstdlib>

#include "game.h"
#include "main_menu.h"
#include "program.h" 
#include "config.h"
#include "metrics.h"
#include "game_util.h"
#include "platform_util.h"
#include "MyGUI.h"




#include <sstream>
#include "noimpl.h"
#include "SDL_main.h"

SDL_Window* getWindow();



namespace Glest {

    bool Window::handleEvent() {
        while (SDL_PollEvent(&mEvent) != 0)
        {
            switch (mEvent.type)
            {
                // keyboard events
            case SDL_KEYDOWN:
                mKeyCode = mEvent.key.keysym.sym;
                if (!keyPressed(mKeyCode, nullptr))
                {
                    /* handle ALT+Return */
                    if (mEvent.key.keysym.sym == SDLK_RETURN
                        && (mEvent.key.keysym.mod & (KMOD_LALT | KMOD_RALT))) {
                        toggleFullscreen();
                    }
                    eventKeyDown(getKey(mEvent.key.keysym));
                    //global_window->eventKeyPress(static_cast<char>(event.key.keysym.unicode));
                    eventKeyPress(static_cast<char>(mEvent.key.keysym.sym));
                }
                break;
            case SDL_TEXTINPUT:
                mKeyCode = SDLK_UNKNOWN;
                keyPressed(mKeyCode, &mEvent.text);
                break;
            case SDL_KEYUP:
                if (!keyReleased(mEvent.key))
                    eventKeyUp(getKey(mEvent.key.keysym));
                break;
                // mouse events
            case SDL_MOUSEMOTION:
                if (!mouseMoved(mEvent.motion))
                {
                    MouseState ms;
                    ms.leftMouse = (mEvent.motion.state & SDL_BUTTON_LMASK) != 0;
                    ms.rightMouse = (mEvent.motion.state & SDL_BUTTON_RMASK) != 0;
                    ms.centerMouse = (mEvent.motion.state & SDL_BUTTON_MMASK) != 0;
                    eventMouseMove(mEvent.motion.x, mEvent.motion.y, &ms);
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (!mousePressed(mEvent.button))
                    handleMouseDown(mEvent);

                break;
            case SDL_MOUSEBUTTONUP:
                if (!mouseReleased(mEvent.button))
                {
                    eventMouseUp(mEvent.button.x, mEvent.button.y, getMouseButton(mEvent.button.button));
                }
                break;
            case SDL_MOUSEWHEEL:
                mouseWheelMoved(mEvent.wheel);
                break;
                // drop file events
            case SDL_DROPFILE:
                break;
                // windows events
            case SDL_WINDOWEVENT:
                switch (mEvent.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    mExit = true;
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    _windowResized(mEvent.window.data1, mEvent.window.data2);
                    break;
                case SDL_WINDOWEVENT_SHOWN:
                case SDL_WINDOWEVENT_RESTORED:
                case SDL_WINDOWEVENT_EXPOSED:
                case SDL_WINDOWEVENT_MAXIMIZED:
                    mWindowOn = true;
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                case SDL_WINDOWEVENT_HIDDEN:
                    mWindowOn = false;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        return true;
    }

    void Window::setText(std::string text) {
        SDL_SetWindowTitle(getWindow(), text.c_str());
    }

    void Window::destroy() {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }


    void Window::toggleFullscreen() {
        mFullScreen = !mFullScreen;
        SDL_SetWindowFullscreen(getWindow(), mFullScreen);
    }

    void Window::handleMouseDown(SDL_Event event) {
        static const Uint32 DOUBLECLICKTIME = 500;
        static const int DOUBLECLICKDELTA = 5;

        MouseButton button = getMouseButton(event.button.button);
        Uint32 ticks = SDL_GetTicks();
        int n = (int)button;
        if (ticks - lastMouseDown[n] < DOUBLECLICKTIME
            && abs(lastMouseX[n] - event.button.x) < DOUBLECLICKDELTA
            && abs(lastMouseY[n] - event.button.y) < DOUBLECLICKDELTA) {
            eventMouseDown(event.button.x, event.button.y, button);
            eventMouseDoubleClick(event.button.x, event.button.y, button);
        }
        else {
            eventMouseDown(event.button.x, event.button.y, button);
        }
        lastMouseDown[n] = ticks;
        lastMouseX[n] = event.button.x;
        lastMouseY[n] = event.button.y;
    }

    MouseButton Window::getMouseButton(int sdlButton) {
        switch (sdlButton) {
        case SDL_BUTTON_LEFT:
            return mbLeft;
        case SDL_BUTTON_RIGHT:
            return mbRight;
        case SDL_BUTTON_MIDDLE:
            return mbCenter;
        default:
            throw std::runtime_error("Mouse Button > 3 not handled.");
        }
    }

    char Window::getKey(SDL_Keysym keysym) {
        switch (keysym.sym) {
        case SDLK_PLUS:
        case SDLK_KP_PLUS:
            return vkAdd;
        case SDLK_MINUS:
        case SDLK_KP_MINUS:
            return vkSubtract;
        case SDLK_LALT:
        case SDLK_RALT:
            return vkAlt;
        case SDLK_LCTRL:
        case SDLK_RCTRL:
            return vkControl;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            return vkShift;
        case SDLK_ESCAPE:
            return vkEscape;
        case SDLK_UP:
            return vkUp;
        case SDLK_LEFT:
            return vkLeft;
        case SDLK_RIGHT:
            return vkRight;
        case SDLK_DOWN:
            return vkDown;
        case SDLK_RETURN:
        case SDLK_KP_ENTER:
            return vkReturn;
        case SDLK_BACKSPACE:
            return vkBack;
        case SDLK_0:
            return '0';
        case SDLK_1:
            return '1';
        case SDLK_2:
            return '2';
        case SDLK_3:
            return '3';
        case SDLK_4:
            return '4';
        case SDLK_5:
            return '5';
        case SDLK_6:
            return '6';
        case SDLK_7:
            return '7';
        case SDLK_8:
            return '8';
        case SDLK_9:
            return '9';
        case SDLK_a:
            return 'A';
        case SDLK_b:
            return 'B';
        case SDLK_c:
            return 'C';
        case SDLK_d:
            return 'D';
        case SDLK_e:
            return 'E';
        case SDLK_f:
            return 'F';
        case SDLK_g:
            return 'G';
        case SDLK_h:
            return 'H';
        case SDLK_i:
            return 'I';
        case SDLK_j:
            return 'J';
        case SDLK_k:
            return 'K';
        case SDLK_l:
            return 'L';
        case SDLK_m:
            return 'M';
        case SDLK_n:
            return 'N';
        case SDLK_o:
            return 'O';
        case SDLK_p:
            return 'P';
        case SDLK_q:
            return 'Q';
        case SDLK_r:
            return 'R';
        case SDLK_s:
            return 'S';
        case SDLK_t:
            return 'T';
        case SDLK_u:
            return 'U';
        case SDLK_v:
            return 'V';
        case SDLK_w:
            return 'W';
        case SDLK_x:
            return 'X';
        case SDLK_y:
            return 'Y';
        case SDLK_z:
            return 'Z';
        default:
            //Uint16 c = keysym.unicode;
            Uint16 c = keysym.sym;
            if ((c & 0xFF80) == 0) {
                return toupper(c);
            }
            break;
        }

        return 0;
    }


// =====================================================
// 	class std::exceptionHandler
// =====================================================

class ExceptionHandler: public PlatformExceptionHandler{
public:
	virtual void handle(){
		message("An error ocurred and Glest will close.\nPlease report this bug to "+mailString+", attaching the generated "+getCrashDumpFileName()+" file.");
	}
};

// =====================================================
// 	class MainWindow
// =====================================================

Window::Window(Program *program){
	this->program= program;

    memset(lastMouseDown, 0, sizeof(lastMouseDown));
}

Window::~Window(){
	delete program;
}

void Window::eventMouseDown(int x, int y, MouseButton mouseButton){
	switch(mouseButton){
	case mbLeft:
		program->mouseDownLeft(x, getH() - y);
		break;
	case mbRight:
		program->mouseDownRight(x, getH() - y);
		break;
	default:
		break;
	}
}

void Window::eventMouseUp(int x, int y, MouseButton mouseButton){
	if(mouseButton==mbLeft){
		program->mouseUpLeft(x, getH() - y);
	}
}

void Window::eventMouseDoubleClick(int x, int y, MouseButton mouseButton){
	if(mouseButton == mbLeft){
		program->mouseDoubleClickLeft(x,  getH() - y);
	}
}

void Window::eventMouseMove(int x, int y, const MouseState *ms){
	program->mouseMove(x, getH() - y, ms);
}

void Window::eventKeyDown(char key){
	program->keyDown(key);
}

void Window::eventKeyUp(char key){
	program->keyUp(key);
}

void Window::eventKeyPress(char c){
	program->keyPress(c);
}

void Window::eventActivate(bool active){
	if(!active){
		//minimize();
	}
}

void Window::eventClose(){
	delete program;
	program= NULL;
}

void Window::showCursor(bool show)
{
    SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}

// =====================================================
// Main
// =====================================================

int glestMain(int argc, char** argv){

	Window *mainWindow= NULL;
	Program *program= NULL;
	ExceptionHandler exceptionHandler;
    exceptionHandler.install(getCrashDumpFileName());

	try{
		program= new Program();
		mainWindow= new Window(program);

		//parse command line
        if (argc == 2 && std::string(argv[1]) == "-server"){
			program->initServer(mainWindow);
		}
        else if (argc == 3 && std::string(argv[1]) == "-client"){
			program->initClient(mainWindow, Ip(argv[2]));
		}
		else{
			program->initNormal(mainWindow);
		}
		
        mainWindow->addResourceLocation(mainWindow->getRootMedia() + "/Demos/Demo_Gui");
        mainWindow->addResourceLocation(mainWindow->getRootMedia() + "/Common/Demos");
        MyGUI::LayoutManager::getInstance().loadLayout("MainPanel.layout");

	    program->loop();
	}
	catch (MyGUI::Exception& _e) {
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
		MessageBoxA(NULL, _e.getFullDescription().c_str(), "An exception has occured", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured" << " : " << _e.getFullDescription().c_str();
#endif
		throw;
	}
    catch (const std::exception &e){
		restoreVideoMode();
		exceptionMessage(e);
	}	

	delete mainWindow;

	return 0;
}

}//end namespace

int main(int argc, char **argv)            
{                                                                   
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)  {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << "\n";
        return 1;
    }

    int result = Glest::glestMain(argc, argv);
    SDL_Quit();
    return result;
}
