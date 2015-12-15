

#ifndef _GLEST_GAME_NETWORKMESSAGE_H_
#define _GLEST_GAME_NETWORKMESSAGE_H_

#include "socket.h"
#include "game_constants.h"
#include "network_types.h"





namespace Glest {

class GameSettings;

enum NetworkMessageType{
	nmtInvalid,
	nmtIntro,
	nmtPing,
	nmtReady,
	nmtLaunch,
	nmtCommandList,
	nmtText,
	nmtQuit,

	nmtCount
};

// =====================================================
//	class NetworkMessage
// =====================================================

class NetworkMessage{
public:
	virtual ~NetworkMessage(){}
	virtual bool receive(Socket* socket)= 0;
	virtual void send(Socket* socket) const = 0;

protected:
	bool receive(Socket* socket, void* data, int dataSize);
	void send(Socket* socket, const void* data, int dataSize) const;
};

// =====================================================
//	class NetworkMessageIntro
//
//	Message sent from the server to the client
//	when the client connects and vice versa
// =====================================================

class NetworkMessageIntro: public NetworkMessage{
private:
	static const int maxVersionStringSize= 64;
	static const int maxNameSize= 16;

private:
	struct Data{
		int8 messageType;
		NetworkString<maxVersionStringSize> versionString;
		NetworkString<maxNameSize> name;
		int16 playerIndex;
	};

private:
	Data data;

public:
	NetworkMessageIntro();
	NetworkMessageIntro(const std::string &versionString, const std::string &name, int playerIndex);

	std::string getVersionString() const		{return data.versionString.getString();}
	std::string getName() const				{return data.name.getString();}
	int getPlayerIndex() const			{return data.playerIndex;}

	virtual bool receive(Socket* socket);
	virtual void send(Socket* socket) const;
};

// =====================================================
//	class NetworkMessageReady
//
//	Message sent at the beggining of the game
// =====================================================

class NetworkMessageReady: public NetworkMessage{
private:
	struct Data{
		int8 messageType;
		int32 checksum;
	};

private:
	Data data;

public:
	NetworkMessageReady();
	NetworkMessageReady(int32 checksum);

	int32 getChecksum() const	{return data.checksum;}

	virtual bool receive(Socket* socket);
	virtual void send(Socket* socket) const;
};

// =====================================================
//	class NetworkMessageLaunch
//
//	Message sent from the server to the client
//	to launch the game
// =====================================================

class NetworkMessageLaunch: public NetworkMessage{
private:
	static const int maxStringSize= 256;

private:
	struct Data{
		int8 messageType;
		NetworkString<maxStringSize> description;
		NetworkString<maxStringSize> map;
		NetworkString<maxStringSize> tileset;
		NetworkString<maxStringSize> tech;
		NetworkString<maxStringSize> factionTypeNames[GameConstants::maxPlayers]; //faction names

		int8 factionControls[GameConstants::maxPlayers];

		int8 thisFactionIndex;
		int8 factionCount;
		int8 teams[GameConstants::maxPlayers];
		int8 startLocationIndex[GameConstants::maxPlayers];
		int8 defaultResources;
        int8 defaultUnits;
        int8 defaultVictoryConditions;
	};

private:
	Data data;

public:
	NetworkMessageLaunch();
	NetworkMessageLaunch(const GameSettings *gameSettings);

	void buildGameSettings(GameSettings *gameSettings) const;

	virtual bool receive(Socket* socket);
	virtual void send(Socket* socket) const;
};

// =====================================================
//	class CommandList
//
//	Message to order a commands to several units
// =====================================================

class NetworkMessageCommandList: public NetworkMessage{
private:
	static const int maxCommandCount= 16*4;
	
private:
	struct Data{
		int8 messageType;
		int8 commandCount;
		int32 frameCount;
		NetworkCommand commands[maxCommandCount];
	};

private:
	Data data;

public:
	NetworkMessageCommandList(int32 frameCount= -1);

	bool addCommand(const NetworkCommand* networkCommand);
	
	void clear()									{data.commandCount= 0;}
	int getCommandCount() const						{return data.commandCount;}
	int getFrameCount() const						{return data.frameCount;}
	const NetworkCommand* getCommand(int i) const	{return &data.commands[i];}

	virtual bool receive(Socket* socket);
	virtual void send(Socket* socket) const;
};

// =====================================================
//	class NetworkMessageText
//
//	Chat text message
// =====================================================

class NetworkMessageText: public NetworkMessage{
private:
	static const int maxStringSize= 64;

private:
	struct Data{
		int8 messageType;
		NetworkString<maxStringSize> text;
		NetworkString<maxStringSize> sender;
		int8 teamIndex;
	};

private:
	Data data;

public:
	NetworkMessageText(){}
	NetworkMessageText(const std::string &text, const std::string &sender, int teamIndex);

	std::string getText() const		{return data.text.getString();}
	std::string getSender() const	{return data.sender.getString();}
	int getTeamIndex() const	{return data.teamIndex;}

	virtual bool receive(Socket* socket);
	virtual void send(Socket* socket) const;
};

// =====================================================
//	class NetworkMessageQuit
//
//	Message sent at the beggining of the game
// =====================================================

class NetworkMessageQuit: public NetworkMessage{
private:
	struct Data{
		int8 messageType;
	};

private:
	Data data;

public:
	NetworkMessageQuit();

	virtual bool receive(Socket* socket);
	virtual void send(Socket* socket) const;
};

}//end namespace

#endif
