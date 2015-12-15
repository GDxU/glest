

#ifndef _GLEST_GAME_TIMEFLOW_H_
#define _GLEST_GAME_TIMEFLOW_H_

#include "tileset.h"
#include "sound.h"

namespace Glest {






// =====================================================
// 	class TimeFlow  
//
/// Raises time related events (day/night cycle) 
// =====================================================

class TimeFlow{
public:
	static const float dusk;
	static const float dawn;

private:
	bool firstTime;
	Tileset *tileset;
	float time;
	float lastTime;
	float timeInc;

public:
	void init(Tileset *tileset);

	float getTime() const				{return time;}
	bool isDay() const					{return time>dawn && time<dusk;}
	bool isNight() const				{return !isDay();}
	bool isTotalNight() const			{return time<dawn+1.f || time>dusk-1.f;}

	void update();
private:
	bool isAproxTime(float time);
};

} //end namespace

#endif
