

#ifndef _GLEST_GAME_CONNECTIONSLOT_H_
#define _GLEST_GAME_CONNECTIONSLOT_H_

#include <vector>

#include "socket.h"

#include "network_interface.h"






namespace Glest {

class ServerInterface;

// =====================================================
//	class ConnectionSlot
// =====================================================

class ConnectionSlot: public NetworkInterface{
private:
	ServerInterface* serverInterface;
	Socket* socket;
	int playerIndex;
	std::string name;
	bool ready;

public:
	ConnectionSlot(ServerInterface* serverInterface, int playerIndex);
	~ConnectionSlot();

	virtual void update();

	void setReady()					{ready= true;}
	const std::string &getName() const	{return name;}
	bool isReady() const			{return ready;}

protected:
	virtual Socket* getSocket()				{return socket;}
	virtual Socket* getSocket() const		{return socket;}

private:
	void close();
};

}//end namespace

#endif
