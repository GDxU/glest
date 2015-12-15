

#include "connection_slot.h"

#include <stdexcept>

#include "conversion.h"
#include "game_util.h"
#include "config.h"
#include "server_interface.h"
#include "network_message.h"





namespace Glest {

// =====================================================
//	class ClientConnection
// =====================================================

ConnectionSlot::ConnectionSlot(ServerInterface* serverInterface, int playerIndex){
	this->serverInterface= serverInterface;
	this->playerIndex= playerIndex;
	socket= NULL;
	ready= false;
}

ConnectionSlot::~ConnectionSlot(){
	close();
}

void ConnectionSlot::update(){
	if(socket==NULL){
		socket= serverInterface->getServerSocket()->accept();

		//send intro message when connected
		if(socket!=NULL){
			NetworkMessageIntro networkMessageIntro(getNetworkVersionString(), socket->getHostName(), playerIndex);
			sendMessage(&networkMessageIntro);
		}
	}
	else{
		if(socket->isConnected()){
			NetworkMessageType networkMessageType= getNextMessageType();

			//process incoming commands
			switch(networkMessageType){
				
				case nmtInvalid:
				case nmtText:
					break;

				//command list
				case nmtCommandList:{
					NetworkMessageCommandList networkMessageCommandList;
					if(receiveMessage(&networkMessageCommandList)){
						for(int i= 0; i<networkMessageCommandList.getCommandCount(); ++i){
							serverInterface->requestCommand(networkMessageCommandList.getCommand(i));
						}
					}
				}
				break;

				//process intro messages
				case nmtIntro:{
					NetworkMessageIntro networkMessageIntro;
					if(receiveMessage(&networkMessageIntro)){
						name= networkMessageIntro.getName();
					}
				}
				break;

				default:
                    throw std::runtime_error("Unexpected message in connection slot: " + intToStr(networkMessageType));
			}
		}
		else{
			close();
		}
	}
}

void ConnectionSlot::close(){
	delete socket;
	socket= NULL;
}

}//end namespace
