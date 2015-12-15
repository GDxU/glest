

#ifndef _GLEST_GAME_WORLD_H_
#define _GLEST_GAME_WORLD_H_

#include "vec.h"
#include "math_util.h"
#include "resource.h"
#include "tech_tree.h"
#include "tileset.h"
#include "console.h"
#include "map.h"
#include "scenario.h"
#include "minimap.h"
#include "logger.h"
#include "stats.h"
#include "time_flow.h"
#include "upgrade.h"
#include "water_effects.h"
#include "faction.h"
#include "unit_updater.h"
#include "random.h"
#include "game_constants.h"

namespace Glest {





class Faction;
class Unit;
class Config;
class Game;
class GameSettings;
class ScriptManager;

// =====================================================
// 	class World
//
///	The game world: Map + Tileset + TechTree
// =====================================================

class World{
private:
	typedef std::vector<Faction> Factions;

public:
	static const int generationArea= 100;
	static const float airHeight;
	static const int indirectSightRange= 5;

private:

	Map map;
	Tileset tileset;
	TechTree techTree;
	TimeFlow timeFlow;
	Scenario scenario;

	UnitUpdater unitUpdater;
    WaterEffects waterEffects;
	Minimap minimap;
    Stats stats;	//BattleEnd will delete this object

	Factions factions;

	Random random;

	ScriptManager* scriptManager;

	int thisFactionIndex;
	int thisTeamIndex;
	int frameCount;
	int nextUnitId;

	//config
	bool fogOfWar;
	int fogOfWarSmoothingFrameSkip;
	bool fogOfWarSmoothing;
	
public:
	World();
	void end(); //to die before selection does

	//get			
	int getMaxPlayers() const						{return map.getMaxPlayers();}
	int getThisFactionIndex() const					{return thisFactionIndex;}
	int getThisTeamIndex() const					{return thisTeamIndex;}
	const Faction *getThisFaction() const			{return &factions[thisFactionIndex];}
	int getFactionCount() const						{return factions.size();}
	const Map *getMap() const 						{return &map;}
	const Tileset *getTileset() const 				{return &tileset;}
	const TechTree *getTechTree() const 			{return &techTree;}
	const Scenario *getScenario() const 			{return &scenario;}
	const TimeFlow *getTimeFlow() const				{return &timeFlow;}
	Tileset *getTileset() 							{return &tileset;}
	Map *getMap() 									{return &map;}
	const Faction *getFaction(int i) const			{return &factions[i];}
	Faction *getFaction(int i) 						{return &factions[i];}
	const Minimap *getMinimap() const				{return &minimap;}
	const Stats *getStats() const					{return &stats;};
	Stats *getStats()								{return &stats;};
	const WaterEffects *getWaterEffects() const		{return &waterEffects;}
	int getNextUnitId()								{return nextUnitId++;}
	int getFrameCount() const						{return frameCount;}

	//init & load
	void init(Game *game, bool createUnits);
	void loadTileset(const std::string &dir, Checksum* checksum);
	void loadTech(const std::string &dir, Checksum* checksum);
	void loadMap(const std::string &path, Checksum* checksum);
	void loadScenario(const std::string &path, Checksum* checksum);
	
	//misc
	void update();
	Unit* findUnitById(int id);
	const UnitType* findUnitTypeById(const FactionType* factionType, int id);
	bool placeUnit(const Vec2i &startLoc, int radius, Unit *unit, bool spaciated= false);
	void moveUnitCells(Unit *unit);
	bool toRenderUnit(const Unit *unit, const Quad2i &visibleQuad) const;
	bool toRenderUnit(const Unit *unit) const;
	Unit *nearestStore(const Vec2i &pos, int factionIndex, const ResourceType *rt);

	//scripting interface
	void createUnit(const std::string &unitName, int factionIndex, const Vec2i &pos);
	void givePositionCommand(int unitId, const std::string &commandName, const Vec2i &pos);
	void giveProductionCommand(int unitId, const std::string &producedName);
	void giveUpgradeCommand(int unitId, const std::string &upgradeName);
	void giveResource(const std::string &resourceName, int factionIndex, int amount);
	int getResourceAmount(const std::string &resourceName, int factionIndex);
	Vec2i getStartLocation(int factionIndex);
	Vec2i getUnitPosition(int unitId);
	int getUnitFactionIndex(int unitId);
	int getUnitCount(int factionIndex);
	int getUnitCountOfType(int factionIndex, const std::string &typeName);

private:
	
	void initCells();
	void initSplattedTextures();
	void initFactionTypes(GameSettings *gs);
	void initMinimap();
	void initUnits();
	void initMap();
	void initExplorationState();
	
	//misc
	void tick();
	void computeFow();
	void exploreCells(const Vec2i &newPos, int sightRange, int teamIndex);
};

}//end namespace

#endif
