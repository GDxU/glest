

#ifndef _GLEST_GAME_NETWORKMANAGER_H_
#define _GLEST_GAME_NETWORKMANAGER_H_

#include <cassert>

#include "socket.h"
#include "checksum.h"
#include "server_interface.h"
#include "client_interface.h"



namespace Glest {

// =====================================================
//	class NetworkManager
// =====================================================

enum NetworkRole{
	nrServer,
	nrClient,
	nrIdle
};

class NetworkManager{
private:
	GameNetworkInterface* gameNetworkInterface;
	NetworkRole networkRole;

public:
	static NetworkManager &getInstance();

	NetworkManager();
	void init(NetworkRole networkRole);
	void end();
	void update();

	bool isNetworkGame();
	GameNetworkInterface* getGameNetworkInterface();
	ServerInterface* getServerInterface();
	ClientInterface* getClientInterface();
};

}//end namespace

#endif
