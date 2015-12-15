

#ifndef _GLEST_GAME_CLIENTINTERFACE_H_
#define _GLEST_GAME_CLIENTINTERFACE_H_

#include <vector>

#include "network_interface.h"
#include "game_settings.h"

#include "socket.h"






namespace Glest {

// =====================================================
//	class ClientInterface
// =====================================================

class ClientInterface: public GameNetworkInterface{
private:
	static const int messageWaitTimeout;
	static const int waitSleepTime;

private:
	ClientSocket *clientSocket;
	GameSettings gameSettings;
	std::string serverName;
	bool introDone;
	bool launchGame;
	int playerIndex;

public:
	ClientInterface();
	virtual ~ClientInterface();

	virtual Socket* getSocket()					{return clientSocket;}
	virtual const Socket* getSocket() const		{return clientSocket;}

	//message processing
	virtual void update();
	virtual void updateLobby();
	virtual void updateKeyframe(int frameCount);
	virtual void waitUntilReady(Checksum* checksum);

	// message sending
	virtual void sendTextMessage(const std::string &text, int teamIndex);
	virtual void quitGame(){}

	//misc
	virtual std::string getNetworkStatus() const;

	//accessors
	std::string getServerName() const			{return serverName;}
	bool getLaunchGame() const				{return launchGame;}
	bool getIntroDone() const				{return introDone;}
	int getPlayerIndex() const				{return playerIndex;}
	const GameSettings *getGameSettings()	{return &gameSettings;}

	void connect(const Ip &ip, int port);
	void reset();

private:
	void waitForMessage();
};

}//end namespace

#endif
