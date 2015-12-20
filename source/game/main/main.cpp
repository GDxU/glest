

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
#include "platform_main.h"
#include "MyGUI.h"




namespace Glest {

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

MainWindow::MainWindow(Program *program){
	this->program= program;
}

MainWindow::~MainWindow(){
	delete program;
}

void MainWindow::eventMouseDown(int x, int y, MouseButton mouseButton){
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

void MainWindow::eventMouseUp(int x, int y, MouseButton mouseButton){
	if(mouseButton==mbLeft){
		program->mouseUpLeft(x, getH() - y);
	}
}

void MainWindow::eventMouseDoubleClick(int x, int y, MouseButton mouseButton){
	if(mouseButton == mbLeft){
		program->mouseDoubleClickLeft(x,  getH() - y);
	}
}

void MainWindow::eventMouseMove(int x, int y, const MouseState *ms){
	program->mouseMove(x, getH() - y, ms);
}

void MainWindow::eventKeyDown(char key){
	program->keyDown(key);
}

void MainWindow::eventKeyUp(char key){
	program->keyUp(key);
}

void MainWindow::eventKeyPress(char c){
	program->keyPress(c);
}

void MainWindow::eventActivate(bool active){
	if(!active){
		//minimize();
	}
}

void MainWindow::eventResize(SizeState sizeState){
	program->resize(sizeState);
}

void MainWindow::eventClose(){
	delete program;
	program= NULL;
}

// =====================================================
// Main
// =====================================================

int glestMain(int argc, char** argv){

	MainWindow *mainWindow= NULL;
	Program *program= NULL;
	ExceptionHandler exceptionHandler;
    exceptionHandler.install(getCrashDumpFileName());

	try{
		Config &config = Config::getInstance();

		showCursor(config.getBool("Windowed"));
		
		program= new Program();
		mainWindow= new MainWindow(program);

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

		//main loop
		while(Window::handleEvent()){
			program->loop();
		}

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

MAIN_FUNCTION(Glest::glestMain)
