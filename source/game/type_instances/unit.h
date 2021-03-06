

#ifndef _GLEST_GAME_UNIT_H_
#define _GLEST_GAME_UNIT_H_

#include "model.h"
#include "upgrade_type.h"
#include "particle.h"
#include "skill_type.h"

namespace Glest {








class Map;
class Faction;
class Unit;
class Command;
class SkillType;
class ResourceType;
class CommandType;
class SkillType;
class UnitType;
class TotalUpgrade;
class UpgradeType;
class Level;
class MorphCommandType;

enum CommandResult{
	crSuccess,
	crFailRes,
	crFailReqs,
	crFailUndefined,
	crSomeFailed
};

enum InterestingUnitType{
	iutIdleHarvester,
	iutBuiltBuilding,
	iutProducer,
	iutDamaged,
	iutStore
};

// =====================================================
// 	class UnitObserver
// =====================================================

class UnitObserver{
public:
	enum Event{
		eKill
	};

public:
	virtual ~UnitObserver() {}
	virtual void unitEvent(Event event, const Unit *unit)=0;
};

// =====================================================
// 	class UnitReference  
// =====================================================

class UnitReference{
private:
	int id;
	Faction *faction;

public:
	UnitReference();

	void operator=(const Unit *unit);
	Unit *getUnit() const;
};

// =====================================================
// 	class UnitPath  
//
/// Holds the next cells of a Unit movement
// =====================================================

class UnitPath{
private:
	static const int maxBlockCount;

private:
	int blockCount;
	std::vector<Vec2i> pathQueue;

public:
	bool isBlocked();
	bool isEmpty();

	void clear();
	void incBlockCount();
	void push(const Vec2i &path);
	Vec2i pop();
};

// ===============================
// 	class Unit
//
///	A game unit or building
// ===============================

class Unit{
private:
    typedef std::list<Command*> Commands;
    typedef std::list<UnitObserver*> Observers;

public:
	static const float speedDivider;
	static const int maxDeadCount;
	static const float highlightTime;
	static const int invalidId;

private:
	int id;
    int hp;
    int ep;
    int loadCount;
    int deadCount;
    float progress;			//between 0 and 1
	float lastAnimProgress;	//between 0 and 1
	float animProgress;		//between 0 and 1
	float highlight;
	int progress2;  
	int kills;

	UnitReference targetRef;

	Field currField;
    Field targetField;
	const Level *level;

    Vec2i pos;
	Vec2i lastPos;
    Vec2i targetPos;		//absolute target pos 
	Vec3f targetVec;
	Vec2i meetingPos;

	float lastRotation;		//in degrees
	float targetRotation;	
	float rotation;			

    const UnitType *type;
    const ResourceType *loadType;
    const SkillType *currSkill;
	
    bool toBeUndertaken;
	bool alive;

    Faction *faction;
	ParticleSystem *fire;
	TotalUpgrade totalUpgrade;
	Map *map;

	UnitPath unitPath;

    Commands commands;
	Observers observers;

public:
    Unit(int id, const Vec2i &pos, const UnitType *type, Faction *faction, Map *map);
    ~Unit();

    //queries
	int getId() const							{return id;}
	Field getCurrField() const					{return currField;}
	int getLoadCount() const					{return loadCount;}
	float getLastAnimProgress() const			{return lastAnimProgress;}
	float getProgress() const					{return progress;}
	float getAnimProgress() const				{return animProgress;}
	float getHightlight() const					{return highlight;}
	int getProgress2() const					{return progress2;}
	int getFactionIndex() const;
	int getTeam() const;
	int getHp() const							{return hp;}
	int getEp() const							{return ep;}
	int getProductionPercent() const;
	float getHpRatio() const;
	float getEpRatio() const;
	bool getToBeUndertaken() const				{return toBeUndertaken;}      
	Vec2i getTargetPos() const					{return targetPos;}
	Vec3f getTargetVec() const					{return targetVec;}
	Field getTargetField() const				{return targetField;}
	Vec2i getMeetingPos() const					{return meetingPos;}
	Faction *getFaction() const					{return faction;}
    const ResourceType *getLoadType() const		{return loadType;}
	const UnitType *getType() const				{return type;}
	const SkillType *getCurrSkill() const		{return currSkill;}
	const TotalUpgrade *getTotalUpgrade() const	{return &totalUpgrade;}
	float getRotation() const					{return rotation;}
	float getVerticalRotation() const;
	ParticleSystem *getFire() const				{return fire;}
	int getKills()								{return kills;}
	const Level *getLevel() const				{return level;}
	const Level *getNextLevel() const;
	std::string getFullName() const;
	const UnitPath *getPath() const				{return &unitPath;}
	UnitPath *getPath()							{return &unitPath;}

    //pos
	Vec2i getPos() const				{return pos;}
	Vec2i getLastPos() const			{return lastPos;}
	Vec2i getCenteredPos() const;
    Vec2f getFloatCenteredPos() const;
	Vec2i getCellPos() const;

    //is
	bool isHighlighted() const			{return highlight>0.f;}
	bool isDead() const					{return !alive;}
	bool isAlive() const				{return alive;}
    bool isOperative() const;
    bool isBeingBuilt() const;
    bool isBuilt() const;
    bool isPutrefacting() const;
	bool isAlly(const Unit *unit) const;
	bool isDamaged() const;
	bool isInteresting(InterestingUnitType iut) const;

    //set
	void setCurrField(Field currField)					{this->currField= currField;}
    void setCurrSkill(const SkillType *currSkill);
    void setCurrSkill(SkillClass sc);
	void setLoadCount(int loadCount)					{this->loadCount= loadCount;}
	void setLoadType(const ResourceType *loadType)		{this->loadType= loadType;}
	void setProgress2(int progress2)					{this->progress2= progress2;}
	void setPos(const Vec2i &pos);
	void setTargetPos(const Vec2i &targetPos);							
	void setTarget(const Unit *unit);					
	void setTargetVec(const Vec3f &targetVec)			{this->targetVec= targetVec;}
	void setMeetingPos(const Vec2i &meetingPos)			{this->meetingPos= meetingPos;}

	//render related
    const Model *getCurrentModel() const;
	Vec3f getCurrVector() const;
	Vec3f getCurrVectorFlat() const;
    
    //command related
	bool anyCommand() const;
	Command *getCurrCommand() const;
	CommandResult giveCommand(Command *command);		//give a command 
	CommandResult finishCommand();						//command finished
	CommandResult cancelCommand();						//cancel canceled

	//lifecycle
	void create(bool startingUnit= false);
	void born();
	void kill();
	void undertake();

	//observers
	void addObserver(UnitObserver *unitObserver) ;
	void removeObserver(UnitObserver *unitObserver);
	void notifyObservers(UnitObserver::Event event);

    //other
	void resetHighlight();
	const CommandType *computeCommandType(const Vec2i &pos, const Unit *targetUnit= NULL) const;
	std::string getDesc() const;
    bool computeEp();
    bool repair();
    bool decHp(int i);
    int update2();
    bool update();
	void tick();
	void applyUpgrade(const UpgradeType *upgradeType);
	void computeTotalUpgrade();
	void incKills();
	bool morph(const MorphCommandType *mct);
	CommandResult checkCommand(Command *command) const;
	void applyCommand(Command *command);

private:
	float computeHeight(const Vec2i &pos) const;
	void updateTarget();
	void clearCommands();
	CommandResult undoCommand(Command *command);
};

}// end namespace

#endif
