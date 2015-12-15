

#include "network_interface.h"

#include <exception>
#include <cassert>

#include "types.h"
#include "conversion.h"
#include "platform_util.h"







namespace Glest {

// =====================================================
//	class NetworkInterface
// =====================================================

const int NetworkInterface::readyWaitTimeout= 60000;	//1 minute


void NetworkInterface::sendMessage(const NetworkMessage* networkMessage){
	Socket* socket= getSocket();

	networkMessage->send(socket);
}

NetworkMessageType NetworkInterface::getNextMessageType(){
	Socket* socket= getSocket();
	int8 messageType= nmtInvalid;

	//peek message type
	if(socket->getDataToRead()>=sizeof(messageType)){
		socket->peek(&messageType, sizeof(messageType));
	}

	//sanity check new message type
	if(messageType<0 || messageType>=nmtCount){
        throw std::runtime_error("Invalid message type: " + intToStr(messageType));
	}

	return static_cast<NetworkMessageType>(messageType);
}

bool NetworkInterface::receiveMessage(NetworkMessage* networkMessage){
	Socket* socket= getSocket();

	return networkMessage->receive(socket);
}

bool NetworkInterface::isConnected(){
	return getSocket()!=NULL && getSocket()->isConnected();
}

// =====================================================
//	class GameNetworkInterface
// =====================================================

GameNetworkInterface::GameNetworkInterface(){
	quit= false;
}

}//end namespace
