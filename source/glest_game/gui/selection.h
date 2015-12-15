

#ifndef _GLEST_GAME_SELECTION_
#define _GLEST_GAME_SELECTION_

#include "unit.h"
#include <vector>




namespace Glest {

class Gui;

// =====================================================
// 	class Selection 
//
///	List of selected units and groups
// =====================================================

class Selection: public UnitObserver{
public:
	typedef std::vector<Unit*> UnitContainer;
	typedef UnitContainer::const_iterator UnitIterator;

public:
	static const int maxGroups= 10;
	static const int maxUnits= 16;

private:
	int factionIndex;
	UnitContainer selectedUnits;
	UnitContainer groups[maxGroups];
	Gui *gui;

public:
	void init(Gui *gui, int factionIndex);
	virtual ~Selection();

	void select(Unit *unit);
	void select(const UnitContainer &units);
	void unSelect(int unitIndex);
	void unSelect(const UnitContainer &units);
	void clear();
	
	bool isEmpty() const				{return selectedUnits.empty();}
	bool isUniform() const;
	bool isEnemy() const;
	bool isComandable() const;
	bool isCancelable() const;
	bool isMeetable() const;
	int getCount() const				{return selectedUnits.size();}
	const Unit *getUnit(int i) const	{return selectedUnits[i];}
	const Unit *getFrontUnit() const	{return selectedUnits.front();}
	Vec3f getRefPos() const;
	bool hasUnit(const Unit* unit) const;
	
	void assignGroup(int groupIndex);
	void recallGroup(int groupIndex);


	virtual void unitEvent(UnitObserver::Event event, const Unit *unit);
};

}//end namespace

#endif
