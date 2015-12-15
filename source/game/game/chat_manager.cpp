

#include "chat_manager.h"

#include "window.h"
#include "console.h"
#include "network_manager.h"
#include "lang.h"



namespace Glest {

// =====================================================
//	class ChatManager
// =====================================================

const int ChatManager::maxTextLenght= 64;

ChatManager::ChatManager(){
	console= NULL;
	editEnabled= false;
	teamMode= false;
	thisTeamIndex= -1;
}

void ChatManager::init(Console* console, int thisTeamIndex){
	this->console= console;
	this->thisTeamIndex= thisTeamIndex;
}

void ChatManager::keyDown(char key){
	
	Lang &lang= Lang::getInstance();

	//toggle team mode
	if(!editEnabled && key=='H'){
		if(teamMode){
			teamMode= false;
			console->addLine(lang.get("ChatMode") + ": " + lang.get("All"));
		}
		else{
			teamMode= true;
			console->addLine(lang.get("ChatMode") + ": " + lang.get("Team"));
		}
	}

	if(key==vkReturn){
		if(editEnabled){
			GameNetworkInterface *gameNetworkInterface= NetworkManager::getInstance().getGameNetworkInterface();

			editEnabled= false;
			if(!text.empty()){
				console->addLine(gameNetworkInterface->getHostName() + ": " + text);
				gameNetworkInterface->sendTextMessage(text, teamMode? thisTeamIndex: -1);
			}
		}
		else{
			editEnabled= true;
			text.clear();
		}
	}
	else if(key==vkBack){
		if(!text.empty()){
			text.erase(text.end() -1);
		}
	}
}

void ChatManager::keyPress(char c){
	if(editEnabled && text.size()<maxTextLenght){
		//space is the first meaningful code
		if(c>=' '){
			text+= c;
		}
	}
}

void ChatManager::updateNetwork(){
	GameNetworkInterface *gameNetworkInterface= NetworkManager::getInstance().getGameNetworkInterface();
	std::string text;
	std::string sender;
	
	if(!gameNetworkInterface->getChatText().empty()){
		int teamIndex= gameNetworkInterface->getChatTeamIndex();
		
		if(teamIndex==-1 || teamIndex==thisTeamIndex){
			console->addLine(gameNetworkInterface->getChatSender()+": "+gameNetworkInterface->getChatText(), true);
		}
	}
}
	
}//end namespace
