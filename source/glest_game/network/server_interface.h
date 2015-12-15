

#ifndef _GLEST_GAME_SERVERINTERFACE_H_
#define _GLEST_GAME_SERVERINTERFACE_H_

#include <vector>

#include "game_constants.h"
#include "network_interface.h"
#include "connection_slot.h"
#include "socket.h"





namespace Glest {

// =====================================================
//	class ServerInterface
// =====================================================

class ServerInterface: public GameNetworkInterface{
private:
	ConnectionSlot* slots[GameConstants::maxPlayers];
	ServerSocket serverSocket;

public:
	ServerInterface();
	virtual ~ServerInterface();

	virtual Socket* getSocket()				{return &serverSocket;}
	virtual const Socket* getSocket() const	{return &serverSocket;}

	//message processing
	virtual void update();
	virtual void updateLobby(){};
	virtual void updateKeyframe(int frameCount);
	virtual void waitUntilReady(Checksum* checksum);

	// message sending
	virtual void sendTextMessage(const std::string &text, int teamIndex);
	virtual void quitGame();

	//misc
	virtual std::string getNetworkStatus() const;

	ServerSocket* getServerSocket()		{return &serverSocket;}
	void addSlot(int playerIndex);
	void removeSlot(int playerIndex);
	ConnectionSlot* getSlot(int playerIndex);
	int getConnectedSlotCount();

	void launchGame(const GameSettings* gameSettings);

private:
	void broadcastMessage(const NetworkMessage* networkMessage, int excludeSlot= -1);
	void updateListen();
};

}//end namespace

#endif
