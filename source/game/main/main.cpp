

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



static SDL_Window* s_window = NULL;

SDL_Window* getWindow() {
    return s_window;
}

namespace Glest {

    static Window* global_window = 0;


    void Window::initGl(){
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // 	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 1);
        // 	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 1);
        // 	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 1);
        // 	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencilBits);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        int flags = SDL_WINDOW_OPENGL;
#if 0
        if (_fullscreen)
            flags |= SDL_WINDOW_FULLSCREEN;
#endif
        SDL_Window* screen = SDL_CreateWindow("Cocos2d SDL ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);

        SDL_GL_CreateContext(screen);

        if (glewInit() != GLEW_OK)
            std::cout << "GLEW init false";

        if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
        {
            std::cout << "Ready for GLSL\n";
        }
        else
        {
            std::cout << "Not totally ready :(\n";
        }

        if (glewIsSupported("GL_VERSION_2_0"))
        {
            std::cout << "Ready for OpenGL 2.0\n";
        }
        else
        {
            std::cout << "OpenGL 2.0 not supported\n";
        }

        SDL_GL_SetSwapInterval(1);

        s_window = screen;

        if (screen == 0) {
            std::ostringstream msg;
            msg << "Couldn't set video mode " << w << "x" << h << " depth-buffer). SDL Error is: " << SDL_GetError();
            throw std::runtime_error(msg.str());
        }
    }

    void Window::swapBuffersGl(){
        SDL_GL_SwapWindow(s_window);
    }

    bool Window::handleEvent() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            try {
                switch (event.type) {
                case SDL_QUIT:
                    return false;
                case SDL_MOUSEBUTTONDOWN:
                    global_window->handleMouseDown(event);
                    break;
                case SDL_MOUSEBUTTONUP: {
                                            global_window->eventMouseUp(event.button.x,
                                                event.button.y, getMouseButton(event.button.button));
                                            break;
                }
                case SDL_MOUSEMOTION: {
                                          MouseState ms;
                                          ms.leftMouse = (event.motion.state & SDL_BUTTON_LMASK) != 0;
                                          ms.rightMouse = (event.motion.state & SDL_BUTTON_RMASK) != 0;
                                          ms.centerMouse = (event.motion.state & SDL_BUTTON_MMASK) != 0;
                                          global_window->eventMouseMove(event.motion.x, event.motion.y, &ms);
                                          break;
                }
                case SDL_KEYDOWN:
                    /* handle ALT+Return */
                    if (event.key.keysym.sym == SDLK_RETURN
                        && (event.key.keysym.mod & (KMOD_LALT | KMOD_RALT))) {
                        toggleFullscreen();
                    }
                    global_window->eventKeyDown(getKey(event.key.keysym));
                    //global_window->eventKeyPress(static_cast<char>(event.key.keysym.unicode));
                    global_window->eventKeyPress(static_cast<char>(event.key.keysym.sym));
                    break;
                case SDL_KEYUP:
                    global_window->eventKeyUp(getKey(event.key.keysym));
                    break;
                }
            }
            catch (std::exception& e) {
                std::cerr << "Couldn't process event: " << e.what() << "\n";
            }
        }

        return true;
    }


    std::string Window::getText() {
        return SDL_GetWindowTitle(getWindow());
    }

    float Window::getAspect() {
        return static_cast<float>(getClientH()) / getClientW();
    }

    void Window::setText(std::string text) {
        SDL_SetWindowTitle(getWindow(), text.c_str());
    }

    void Window::setSize(int w, int h) {
        this->w = w;
        this->h = h;

        SDL_SetWindowSize(getWindow(), w, h);
    }

    void Window::setPos(int x, int y)  {
        if (x != 0 || y != 0) {
            NOIMPL;
            return;
        }
    }

    void Window::minimize() {
        NOIMPL;
    }

    void Window::setEnabled(bool enabled) {
        NOIMPL;
    }

    void Window::setVisible(bool visible) {
        NOIMPL;
    }

    void Window::create(int w, int h, bool fullscreen) {
        this->w = w;
        this->h = h;
        _fullscreen = fullscreen;
        initGl();
    }

    void Window::destroy() {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }

    void Window::toggleFullscreen() {
        //SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
        global_window->_fullscreen = !global_window->_fullscreen;
        SDL_SetWindowFullscreen(getWindow(), !!global_window->_fullscreen);
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
    global_window = this;
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

// =====================================================
// Main
// =====================================================

int glestMain(int argc, char** argv){

	Window *mainWindow= NULL;
	Program *program= NULL;
	ExceptionHandler exceptionHandler;
    exceptionHandler.install(getCrashDumpFileName());

	try{
		Config &config = Config::getInstance();

		showCursor(config.getBool("Windowed"));
		
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
