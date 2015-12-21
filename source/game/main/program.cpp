

#include "program.h"

#include "sound.h"
#include "renderer.h"
#include "config.h"
#include "game.h"
#include "main_menu.h"
#include "logo.h"
#include "world.h"
#include "main.h"
#include "sound_renderer.h"
#include "logger.h"
#include "core_data.h"
#include "metrics.h"
#include "network_manager.h"
#include "menu_state_custom_game.h"
#include "menu_state_join_game.h"



// =====================================================
// 	class Program
// =====================================================

namespace Glest {

const int Program::maxTimes= 10;

// ===================== PUBLIC ======================== 

Program::Program(){
    _timeStep = 0;
	fps_ = 0;
	programState= NULL;
}

void Program::initNormal(Window *window){
	init(window);
	setState(new Logo(this));
}

void Program::initServer(Window *window){
	MainMenu* mainMenu= NULL;
	
	init(window);
	mainMenu= new MainMenu(this);
	setState(mainMenu);
	mainMenu->setState(new MenuStateCustomGame(this, mainMenu, true));
}

void Program::initClient(Window *window, const Ip &serverIp){
	MainMenu* mainMenu= NULL;
	
	init(window);
	mainMenu= new MainMenu(this);
	setState(mainMenu);
	mainMenu->setState(new MenuStateJoinGame(this, mainMenu, true, serverIp));
}

Program::~Program(){
	delete programState;
	
	Renderer::getInstance().end();
}

void Program::mouseDownLeft(int x, int y){    
	const Metrics &metrics= Metrics::getInstance();
	programState->mouseDownLeft(metrics.toVirtualX(x), metrics.toVirtualY(y));
}

void Program::mouseUpLeft(int x, int y){
	const Metrics &metrics= Metrics::getInstance();
	programState->mouseUpLeft(metrics.toVirtualX(x), metrics.toVirtualY(y));
}

void Program::mouseDownRight(int x, int y){
	const Metrics &metrics= Metrics::getInstance();
	programState->mouseDownRight(metrics.toVirtualX(x), metrics.toVirtualY(y)); 
}

void Program::mouseDoubleClickLeft(int x, int y){
	const Metrics &metrics= Metrics::getInstance();
	programState->mouseDoubleClickLeft(metrics.toVirtualX(x), metrics.toVirtualY(y));   
}

void Program::mouseMove(int x, int y, const MouseState *ms){
	const Metrics &metrics= Metrics::getInstance();
	programState->mouseMove(metrics.toVirtualX(x), metrics.toVirtualY(y), ms);
}

void Program::keyDown(char key){
	//delegate event
	programState->keyDown(key);
}

void Program::keyUp(char key){        
	programState->keyUp(key);
}

void Program::keyPress(char c){
	programState->keyPress(c);
}

void Program::init(Window *window){

    this->window = window;
    Config &config = Config::getInstance();

    //timers
    _fpsTimer.Reset();// 1, maxTimes);
    _fpsDisplayTimer.Reset();

    //log start
    Logger &logger = Logger::getInstance();
    logger.setFile("glest.log");
    logger.clear();

    //lang
    Lang &lang = Lang::getInstance();
    lang.loadStrings(config.getString("Lang"));

    //window
    window->setText("Glest");
    window->showCursor(config.getBool("Windowed"));
    window->create(config.getInt("ScreenWidth"), config.getInt("ScreenHeight"), config.getBool("Windowed"));

    CoreData::getInstance().load(); //coreData, needs renderer, but must load before renderer init
    Renderer::getInstance().init();	//init renderer (load global textures)
    SoundRenderer::getInstance().init();

}

void Program::loop(){
	Renderer &renderer = Renderer::getInstance();

    while (window->handleEvent()){
        programState->update(_timeStep);

        programState->updateCamera();

        Widget::update();
        SoundRenderer::getInstance().update();
        NetworkManager::getInstance().update();

        programState->render();
        programState->tick();


        if (_fpsDisplayTimer.GetUSec(false) >= 500000)
        {
            fps_ = 1.0f / _timeStep;
            _fpsDisplayTimer.Reset();
        }

        CoreData &coreData = CoreData::getInstance();
        renderer.renderText("FPS: " + floatToStr(fps_), coreData.getMenuFontNormal(), Vec3f(1.f), 10, 10, false);

        window->drawOneFrame();
        ApplyFrameLimit();
    }
}


void Program::ApplyFrameLimit()
{
    long long targetMax = 1000000LL / GameConstants::updateFps;
    long long elapsed = 0;

    for (;;)
    {
        elapsed = _fpsTimer.GetUSec(false);
        if (elapsed >= targetMax)
            break;

        // Sleep if 1 ms or more off the frame limiting goal
        if (targetMax - elapsed >= 1000LL)
        {
            unsigned sleepTime = (unsigned)((targetMax - elapsed) / 1000LL);
            Time::Sleep(sleepTime);
        }
    }

    elapsed = _fpsTimer.GetUSec(true);

    _timeStep = elapsed / 1000000.0f;
}

void Program::setState(ProgramState *programState){
	
	delete this->programState;
	
	this->programState= programState;
	programState->load();
	programState->init();
}
		
void Program::exit(){
	window->destroy();
}

// ==================== PRIVATE ==================== 


}//end namespace
