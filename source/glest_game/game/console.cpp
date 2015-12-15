

#include "console.h"

#include "lang.h"
#include "config.h"
#include "program.h"
#include "game_constants.h"
#include "sound_renderer.h"
#include "core_data.h"

namespace Glest {

// =====================================================
// 	class Console
// =====================================================

Console::Console(){
	//config
	maxLines= Config::getInstance().getInt("ConsoleMaxLines");
	timeout= Config::getInstance().getInt("ConsoleTimeout");

	timeElapsed= 0.0f;
}

void Console::addStdMessage(const std::string &s){
	addLine(Lang::getInstance().get(s));
}

void Console::addLine(std::string line, bool playSound){
	if(playSound){
		SoundRenderer::getInstance().playFx(CoreData::getInstance().getClickSoundA());
	}
	lines.insert(lines.begin(), StringTimePair(line, timeElapsed));
	if(lines.size()>maxLines){
		lines.pop_back();
	}
}

void Console::update(){
	timeElapsed+= 1.f/GameConstants::updateFps;
	
	if(!lines.empty()){
		if(lines.back().second<timeElapsed-timeout){
			lines.pop_back();
		}
    }   
}

bool Console::isEmpty(){
	return lines.empty();   
}
         

}//end namespace
