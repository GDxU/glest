

#ifndef _GLEST_GAME_SCRIPT_MANAGER_H_
#define _GLEST_GAME_SCRIPT_MANAGER_H_

#include <string>
#include <queue>

#include "lua_script.h"
#include "vec.h"

#include "components.h"
#include "game_constants.h"









namespace Glest {

class World;
class Unit;
class GameCamera;

// =====================================================
//	class ScriptManagerMessage
// =====================================================

class ScriptManagerMessage{
private:
	std::string text;
	std::string header;

public:
	ScriptManagerMessage(std::string text, std::string header)	{this->text= text, this->header= header;}
	const std::string &getText() const	{return text;}
	const std::string &getHeader() const	{return header;}
};

class PlayerModifiers{
public:
	PlayerModifiers();

	void disableAi()			{aiEnabled= false;}
	void setAsWinner()			{winner= true;}

	bool getWinner() const		{return winner;}
	bool getAiEnabled() const	{return aiEnabled;}

private:
	bool winner;
	bool aiEnabled;
};

// =====================================================
//	class ScriptManager
// =====================================================

class ScriptManager{
private:
	typedef std::queue<ScriptManagerMessage> MessageQueue;

private:

	//lua
	std::string code;
	LuaScript luaScript;

	//world
	World *world;
	GameCamera *gameCamera;

	//misc
	MessageQueue messageQueue;
	GraphicMessageBox messageBox;
	std::string displayText;
	
	//last created unit
	std::string lastCreatedUnitName;
	int lastCreatedUnitId;

	//last dead unit
	std::string lastDeadUnitName;
	int lastDeadUnitId;

	// end game state
	bool gameOver;
	PlayerModifiers playerModifiers[GameConstants::maxPlayers];

private:
	static ScriptManager* thisScriptManager;

private:
	static const int messageWrapCount;
	static const int displayTextWrapCount;

public:
	void init(World* world, GameCamera *gameCamera);

	//message box functions
	bool getMessageBoxEnabled() const									{return !messageQueue.empty();}
	GraphicMessageBox* getMessageBox()									{return &messageBox;}
	std::string getDisplayText() const										{return displayText;}
	bool getGameOver() const											{return gameOver;}
	const PlayerModifiers *getPlayerModifiers(int factionIndex) const	{return &playerModifiers[factionIndex];}	

	//events
	void onMessageBoxOk();
	void onResourceHarvested();
	void onUnitCreated(const Unit* unit);
	void onUnitDied(const Unit* unit);

private:

	std::string wrapString(const std::string &str, int wrapCount);

	//wrappers, commands
	void showMessage(const std::string &text, const std::string &header);
	void clearDisplayText();
	void setDisplayText(const std::string &text);
	void setCameraPosition(const Vec2i &pos);
	void createUnit(const std::string &unitName, int factionIndex, Vec2i pos);
	void giveResource(const std::string &resourceName, int factionIndex, int amount);
	void givePositionCommand(int unitId, const std::string &producedName, const Vec2i &pos);
	void giveProductionCommand(int unitId, const std::string &producedName);
	void giveUpgradeCommand(int unitId, const std::string &upgradeName);
	void disableAi(int factionIndex);
	void setPlayerAsWinner(int factionIndex);
	void endGame();

	//wrappers, queries
	Vec2i getStartLocation(int factionIndex);
	Vec2i getUnitPosition(int unitId);
	int getUnitFaction(int unitId);
	int getResourceAmount(const std::string &resourceName, int factionIndex);
	const std::string &getLastCreatedUnitName();
	int getLastCreatedUnitId();
	const std::string &getLastDeadUnitName();
	int getLastDeadUnitId();
	int getUnitCount(int factionIndex);
	int getUnitCountOfType(int factionIndex, const std::string &typeName);

	//callbacks, commands
	static int showMessage(LuaHandle* luaHandle);
	static int setDisplayText(LuaHandle* luaHandle);
	static int clearDisplayText(LuaHandle* luaHandle);
	static int setCameraPosition(LuaHandle* luaHandle);
	static int createUnit(LuaHandle* luaHandle);
	static int giveResource(LuaHandle* luaHandle);
	static int givePositionCommand(LuaHandle* luaHandle);
	static int giveProductionCommand(LuaHandle* luaHandle);
	static int giveUpgradeCommand(LuaHandle* luaHandle);
	static int disableAi(LuaHandle* luaHandle);
	static int setPlayerAsWinner(LuaHandle* luaHandle);
	static int endGame(LuaHandle* luaHandle);

	//callbacks, queries
	static int getStartLocation(LuaHandle* luaHandle);
	static int getUnitPosition(LuaHandle* luaHandle);
	static int getUnitFaction(LuaHandle* luaHandle);
	static int getResourceAmount(LuaHandle* luaHandle);
	static int getLastCreatedUnitName(LuaHandle* luaHandle);
	static int getLastCreatedUnitId(LuaHandle* luaHandle);
	static int getLastDeadUnitName(LuaHandle* luaHandle);
	static int getLastDeadUnitId(LuaHandle* luaHandle);
	static int getUnitCount(LuaHandle* luaHandle);
	static int getUnitCountOfType(LuaHandle* luaHandle);
};

}//end namespace

#endif
