

#include "logger.h"

#include "util.h"
#include "renderer.h"
#include "core_data.h"
#include "metrics.h"
#include "lang.h"
#include "main.h"




namespace Glest {

// =====================================================
//	class Logger
// =====================================================

const int Logger::logLineCount= 15;

// ===================== PUBLIC ======================== 

Logger::Logger(){
	fileName= "log.txt";
}

Logger & Logger::getInstance(){
	static Logger logger;
	return logger;
}

void Logger::add(const std::string &str,  bool renderScreen){
	FILE *f=fopen(fileName.c_str(), "at+");
	if(f!=NULL){
		fprintf(f, "%s\n", str.c_str());
		fclose(f);
	}
	current= str;
	if(renderScreen){
		renderLoadingScreen();
	}
}

void Logger::clear(){
    std::string s="Log file\n";

	FILE *f= fopen(fileName.c_str(), "wt+");
	if(f==NULL){
        throw std::runtime_error("Error opening log file" + fileName);
	}
    
    fprintf(f, "%s", s.c_str());
	fprintf(f, "\n");

    fclose(f);
}

// ==================== PRIVATE ==================== 

void Logger::renderLoadingScreen(){

	Renderer &renderer= Renderer::getInstance();
	CoreData &coreData= CoreData::getInstance();
	const Metrics &metrics= Metrics::getInstance();

	renderer.reset2d();
	renderer.clearBuffers();

	renderer.renderBackground(CoreData::getInstance().getBackgroundTexture());
	
	renderer.renderText(
		state, coreData.getMenuFontBig(), Vec3f(1.f), 
		metrics.getVirtualW()/4, 65*metrics.getVirtualH()/100, false);

	renderer.renderText(
		current, coreData.getMenuFontNormal(), 1.0f, 
		metrics.getVirtualW()/4, 
		62*metrics.getVirtualH()/100, false);
	
    Window::swapBuffersGl();
}

}//end namespace
